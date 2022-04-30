#include "editor.h"

Editor::Editor(QObject *parent)
    : QObject{parent}
{
    coverImageProvider = new CoverImageProvider(this);
}

CoverImageProvider::CoverImageProvider(Editor *parent)
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage CoverImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return image;
}

void Editor::readFile(QString path)
{
    if (!mpegfile)
        delete mpegfile;
    file.setFileName(path);
    lastModifiedTime = file.fileTime(QFileDevice::FileModificationTime);
    mpegfile = new TagLib::MPEG::File(QFile::encodeName("/home/redbear/冥月 瑶山百霊 - Eschatology.mp3").constData());
}

QString Editor::getName()
{
    return mpegfile->tag()->title().toCString(true);
}

QString Editor::getArtist()
{
    return mpegfile->tag()->artist().toCString(true);
}

QString Editor::getAlbum()
{
    return mpegfile->tag()->album().toCString(true);
}

void Editor::getCover()
{
    auto tag = mpegfile->ID3v2Tag(false);
    auto list = tag->frameListMap()["APIC"];
    if (!list.isEmpty())
    {
        auto frame = list.front();
        auto pic = reinterpret_cast<TagLib::ID3v2::AttachedPictureFrame *>(frame);
        if (pic && !pic->picture().isNull())
        {
            if (coverImageProvider->image.loadFromData(QByteArray::fromRawData(pic->picture().data(), pic->picture().size())))
            {
                // covpic = cover.scaled(
                //     50,
                //     50,
                //     Qt::IgnoreAspectRatio,
                //     Qt::SmoothTransformation);
                qDebug() << "读取MP3封面信息成功";
            }
        }
        else
        {
            qDebug() << "读取音乐封面信息失败";
        }
    }
}