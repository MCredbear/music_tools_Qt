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

QString Editor::getTitle()
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

QString Editor::getDisk()
{
    QString disk = "";
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(false);
        auto list = tag->frameListMap()["TPOS"];
        if (!list.isEmpty())
            disk = QString::fromStdWString(list.front()->toString().toWString()); // cannot be Bit8
        break;
    }
    case flac:
    {
        TagLib::Ogg::XiphComment *tag = flacFile->xiphComment();
        if (tag->contains("DISCNUMBER"))
            disk = tag->fieldListMap().operator[]("DISCNUMBER").toString().data(TagLib::String::UTF8).data();
        break;
    }
    }
    return disk;
}

QString Editor::getTrack()
{
    QString track = "";
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(false);
        track = QString::number(tag->track());
        break;
    }
    case flac:
    {
        TagLib::Ogg::XiphComment *tag = flacFile->xiphComment();
        track = QString::number(tag->track());
        break;
    }
    }
    if (track == "0")
        track = "";
    return track;
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
        TagLib::Ogg::XiphComment *tag = flacFile->xiphComment();
        if (tag->contains("LYRICS"))
            lyric = tag->fieldListMap().operator[]("LYRICS").toString().data(TagLib::String::UTF8).data();
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

void Editor::setTitle(QString title)
{
    switch (format)
    {
    case mp3:
        mpegFile->tag()->setTitle(title.toStdWString());
        break;
    case flac:
        flacFile->tag()->setTitle(title.toStdWString());
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

void Editor::setDisk(QString disk)
{
    switch (format)
    {
    case mp3:
    {
        auto tag = mpegFile->ID3v2Tag(true);
        auto list = tag->frameListMap()["TPOS"];
        list.front()->setText(disk.toStdString());
        break;
    }
    case flac:
    {
        TagLib::Ogg::XiphComment *tag = flacFile->xiphComment(true);
        tag->addField("DISCNUMBER", disk.toStdWString(), true);
        break;
    }
    }
}

void Editor::setTrack(QString track)
{
    if (track != "")
    {
        switch (format)
        {
        case mp3:
        {
            auto tag = mpegFile->ID3v2Tag(true);
            tag->setTrack(track.toUInt());
            break;
        }
        case flac:
        {
            TagLib::Ogg::XiphComment *tag = flacFile->xiphComment(true);
            tag->setTrack(track.toUInt());
            break;
        }
        }
    }
    else
    {
        switch (format)
        {
        case mp3:
        {
            auto tag = mpegFile->ID3v2Tag(true);
            tag->setTrack(0);
            break;
        }
        case flac:
        {
            TagLib::Ogg::XiphComment *tag = flacFile->xiphComment(true);
            tag->setTrack(0);
            break;
        }
        }
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
        if (list.isEmpty())
        {
            TagLib::ID3v2::UnsynchronizedLyricsFrame *frame = new TagLib::ID3v2::UnsynchronizedLyricsFrame;
            frame->setText(lyric.toStdString());
            tag->addFrame(frame);
        }
        else
        {
            list.front()->setText(lyric.toStdString());
        }
        break;
    }
    case flac:
    {
        TagLib::Ogg::XiphComment *tag = flacFile->xiphComment(true);
        tag->addField("LYRICS", lyric.toStdWString(), true);
        break;
    }
    }
}

void Editor::setYear(QString year)
{
    if (year != "")
    {
        switch (format)
        {
        case mp3:
            mpegFile->tag()->setYear(year.toInt());
            break;
        case flac:
            flacFile->tag()->setYear(year.toInt());
            break;
        }
    }
}