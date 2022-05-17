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
    if (!mpegFile)
        delete mpegFile;
    if (!flacFile)
        delete flacFile;
    if (!mp4File)
        delete mp4File;
    qDebug() << "readed";
    file.setFileName(path);
    lastModifiedTime = file.fileTime(QFileDevice::FileModificationTime);
    QFileInfo fileInfo = QFileInfo(path);
    QString formatS = fileInfo.completeSuffix();

    if (!formatS.compare("mp3", Qt::CaseInsensitive))
        format = mp3;
    if (!formatS.compare("flac", Qt::CaseInsensitive))
        format = flac;
    if (!formatS.compare("m4a", Qt::CaseInsensitive))
        format = m4a;
    if (!formatS.compare("wav", Qt::CaseInsensitive))
        format = wav;
    if (!formatS.compare("ogg", Qt::CaseInsensitive))
        format = ogg;
    switch (format)
    {
    case mp3:
        mpegFile = new TagLib::MPEG::File(QFile::encodeName(path).constData());
        break;
    case flac:
        flacFile = new TagLib::FLAC::File(QFile::encodeName(path).constData());
        break;
    case m4a:
        mp4File = new TagLib::MP4::File(QFile::encodeName(path).constData());
        break;
    }
}

QString Editor::getName()
{
    switch (format)
    {
    case mp3:
        return mpegFile->tag()->title().toCString(true);
        break;
    case flac:
        return flacFile->tag()->title().toCString(true);
        break;
    case m4a:
        return mp4File->tag()->title().toCString(true);
        break;
    }
}

QString Editor::getArtist()
{
    switch (format)
    {
    case mp3:
        return mpegFile->tag()->artist().toCString(true);
        break;
    case flac:
        return flacFile->tag()->artist().toCString(true);
        break;
    case m4a:
        return mp4File->tag()->artist().toCString(true);
        break;
    }
}

QString Editor::getAlbum()
{
    switch (format)
    {
    case mp3:
        return mpegFile->tag()->album().toCString(true);
        break;
    case flac:
        return flacFile->tag()->album().toCString(true);
        break;
    case m4a:
        return mp4File->tag()->album().toCString(true);
        break;
    }
}

void Editor::getCover()
{
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(false);
        auto list = tag->frameListMap()["APIC"];
        if (!list.isEmpty())
        {
            auto frame = list.front();
            auto pic = reinterpret_cast<TagLib::ID3v2::AttachedPictureFrame *>(frame);
            if (pic && !pic->picture().isNull())
            {
                if (coverImageProvider->image.loadFromData(QByteArray::fromRawData(pic->picture().data(), pic->picture().size())))
                {
                    qDebug() << "读取MP3封面信息成功";
                }
            }
            else
            {
                qDebug() << "读取音乐封面信息失败";
            }
        }
        break;
    }
    case flac:
    {
        auto list = flacFile->pictureList();
        if (!list.isEmpty())
        {
            auto pic = list[0];
            if (coverImageProvider->image.loadFromData(QByteArray::fromRawData(pic->data().data(), pic->data().size())))
            {
                qDebug() << "读取FLAC封面信息成功";
            }
            else
            {
                qDebug() << "读取音乐封面信息失败";
            }
        }
        break;
    }
    }
}

QString Editor::getLyric()
{
    QString lyric = "";
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(false);
        auto list = tag->frameListMap()["USLT"];
        if (!list.front()->toString().isNull())
            lyric = QString::fromStdWString(list.front()->toString().toWString()); // cannot be Bit8
    }
    break;
    case flac:
    {
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        file.close();
        QByteArray begin = QByteArray::fromHex("0000004c59524943533d"); // "\x00\x00\x00LYRIC="
        QByteArray end = QByteArray::fromHex("000000");
        for (int i = 0; i < data.length(); i++)
        {
            if (data.mid(i, begin.length()) == begin)
            {   
                for (int j = i + begin.length(); j < data.length() - end.length(); j++)
                {
                    if (data.mid(j, end.length()) == end)
                    {
                        lyric = data.mid(i + begin.length(), j - i - begin.length());
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
    }
    return lyric;
}