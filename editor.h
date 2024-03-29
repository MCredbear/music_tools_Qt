#ifndef EDITOR_H
#define EDITOR_H

#include "QObject"
#include "QDebug"
#include "QFile"
#include "QFileInfo"
#include "QDateTime"
#include "QQuickImageProvider"
#include "mpegfile.h"
#include "flacfile.h"
#include "mp4file.h"
#include "wavfile.h"
#include "apefile.h"
#include "id3v2tag.h"
#include "unsynchronizedlyricsframe.h"
#include "tag.h"
#include "attachedpictureframe.h"
#include "flacpicture.h"
#include "xiphcomment.h"
#include "flacproperties.h"

#include "toast.h"

class Editor;
class CoverImageProvider;

class Editor : public QObject
{
    Q_OBJECT
public:
    Editor(QObject *parent = nullptr);
    ~Editor();

    enum formats {mp3, flac, m4a, wav, ogg};
    formats format;

    QFile file;
    QFileInfo fileInfo;
    QByteArray data;
    TagLib::MPEG::File *mpegFile;
    TagLib::FLAC::File *flacFile;
    TagLib::MP4::File *mp4File;
    QDateTime lastModifiedTime;

    Q_INVOKABLE void readFile(QString path);
    Q_INVOKABLE void saveFile();
    
    Q_INVOKABLE QString getTitle();
    Q_INVOKABLE QString getArtist();
    Q_INVOKABLE QString getAlbum();
    Q_INVOKABLE void getCover();
    Q_INVOKABLE QString getDisk();
    Q_INVOKABLE QString getTrack();
    Q_INVOKABLE QString getLyric();
    Q_INVOKABLE QString getYear();
    CoverImageProvider *coverImageProvider;

    Q_INVOKABLE void setTitle(QString title);
    Q_INVOKABLE void setArtist(QString artist);
    Q_INVOKABLE void setAlbum(QString album);
    Q_INVOKABLE void setDisk(QString disk);
    Q_INVOKABLE void setTrack(QString track);
    // Q_INVOKABLE void setCover(QString path);
    Q_INVOKABLE void setLyric(QString lyric);
    Q_INVOKABLE void setYear(QString year);

    Toast *toast;

signals:

};

class CoverImageProvider : public QQuickImageProvider
{
public:
    explicit CoverImageProvider(Editor *parent = nullptr);

    QImage image;

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // EDITOR_H
