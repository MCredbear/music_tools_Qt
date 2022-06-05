#include "editor.h"

Editor::Editor(QObject *parent)
    : QObject{parent}
{
    coverImageProvider = new CoverImageProvider(this);
}

Editor::~Editor()
{
    fileInfo.~QFileInfo(); //虽然会报 malloc(): unsorted double linked list corrupted，但是至少能解决关闭程序后文件时间有被修改的问题
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
    fileInfo.setFile(file);
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

void Editor::saveFile()
{
    switch (format)
    {
    case mp3:
        if (mpegFile->save())
        {
            if (file.open(QIODevice::ReadWrite))
            {
                if (file.setFileTime(lastModifiedTime, QFileDevice::FileModificationTime))
                {
                    toast->sendToast("保存成功");
                    file.close();
                }
                else
                    toast->sendToast("保存失败");
            }
            else
                toast->sendToast("保存失败");
        }
        else
            toast->sendToast("保存失败");
        break;
    case flac:
        if (flacFile->save())
        {
            if (file.open(QIODevice::ReadWrite))
            {
                if (file.setFileTime(lastModifiedTime, QFileDevice::FileModificationTime))
                {
                    toast->sendToast("保存成功");
                    file.close();
                }
                else
                    toast->sendToast("保存失败");
            }
            else
                toast->sendToast("保存失败");
        }
        else
            toast->sendToast("保存失败");
        break;
    case m4a:
        if (mp4File->save())
        {
            if (file.open(QIODevice::ReadWrite))
            {
                if (file.setFileTime(lastModifiedTime, QFileDevice::FileModificationTime))
                {
                    toast->sendToast("保存成功");
                    file.close();
                }
                else
                    toast->sendToast("保存失败");
            }
            else
                toast->sendToast("保存失败");
        }
        else
            toast->sendToast("保存失败");
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
        if (!list.isEmpty())
            lyric = QString::fromStdWString(list.front()->toString().toWString()); // cannot be Bit8
    }
    break;
    case flac:
    {
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        QByteArray head = "LYRICS=";
        unsigned int size = 0;
        for (int i = 0; i < data.length(); i++)
        {
            if (data.mid(i, head.length()) == head)
            {
                for (int j = i - 1; j >= i - 4; j--) 
                {
                    unsigned char B = data.at(j);
                    size = (size << 8) + B; // "bf0e0300"H = 30ebfH = 200383D
                }
                lyric = data.mid(i + head.length(), size - head.length()); qDebug()<<size;
                break;
            }
        }
        break;
    }
    }
    return lyric;
}

QString Editor::getYear()
{
    QString year;
    switch (format)
    {
    case mp3:
        year = QString::number(mpegFile->tag()->year());
        break;
    case flac:
        year = QString::number(flacFile->tag()->year());
        break;
    case m4a:
        year = QString::number(mp4File->tag()->year());
        break;
    }
    if (year == "0")
        return "";
    else
        return year;
}

void Editor::setName(QString name)
{
    switch (format)
    {
    case mp3:
        mpegFile->tag()->setTitle(name.toStdWString());
        break;
    case flac:
        flacFile->tag()->setTitle(name.toStdWString());
        break;
    }
}

void Editor::setArtist(QString artist)
{
    switch (format)
    {
    case mp3:
        mpegFile->tag()->setArtist(artist.toStdWString());
        break;
    case flac:
        flacFile->tag()->setArtist(artist.toStdWString());
        break;
    }
}

void Editor::setAlbum(QString album)
{
    switch (format)
    {
    case mp3:
        mpegFile->tag()->setAlbum(album.toStdWString());
        break;
    case flac:
        flacFile->tag()->setAlbum(album.toStdWString());
        break;
    }
}

void Editor::setLyric(QString lyric)
{
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(true);
        auto list = tag->frameListMap()["USLT"];
        list.front()->setText(lyric.toStdString());
    }
    break;
    case flac:
    {
        // saveFile(); //因为写flac的歌词的方法不是taglib实现的，所以得先保存taglib的标签然后重新读取
        file.open(QIODevice::ReadWrite);
        data = file.readAll();
        file.seek(0);
        bool hasLyric = false;
        QByteArray head = QByteArray::fromHex("0000004c59524943533d"); // "\x00\x00\x00LYRIC="
        QByteArray tail = QByteArray::fromHex("000000");
        for (int i = 0; i < data.length(); i++)
        {
            if (data.mid(i, head.length()) == head)
            {
                for (int j = i + head.length(); j < data.length() - tail.length(); j++)
                {
                    if (data.mid(j, tail.length()) == tail)
                    {
                        data = data.left(i + head.length()) + lyric.toUtf8() + data.right(data.length() - j); qDebug()<<"found";
                        hasLyric = true;
                        break;
                    }
                }
                break;
            }
        }
        if (!hasLyric)
        {
            QByteArray titleHead = QByteArray::fromHex("0000005449544c45"); // "\x00\x00\x00TITLE"
            for (int i = 0; i < data.length(); i++)
            {
                if (data.mid(i, titleHead.length()) == titleHead)
                {
                    data = data.left(i - 1) + head + lyric.toUtf8() + data.right(data.length() - i); qDebug()<<i;
                    break;
                }
            }
        }
        
        file.write(data);
        file.close();
        // delete flacFile;
        // flacFile = new TagLib::FLAC::File(QFile::encodeName(file.fileName()).constData()); //因为写flac的歌词的方法不是taglib实现的，所以taglib的标签得重新读取
    }
    break;
    }
}