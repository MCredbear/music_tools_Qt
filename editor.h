#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QQuickImageProvider>
#include <taglib/taglib.h>
#include <taglib/mpegfile.h>
#include <taglib/flacfile.h>
#include <taglib/mp4file.h>
#include <taglib/wavfile.h>
#include <taglib/apefile.h>
#include <taglib/id3v2tag.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/flacpicture.h>
#include <taglib/xiphcomment.h>
#include <taglib/flacproperties.h>

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
    QString name;
    QString artist;
    QString album;

    Q_INVOKABLE void readFile(QString path);
    Q_INVOKABLE void saveFile();
    
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getArtist();
    Q_INVOKABLE QString getAlbum();
    Q_INVOKABLE void getCover();
    Q_INVOKABLE QString getLyric();
    Q_INVOKABLE QString getYear();
    CoverImageProvider *coverImageProvider;

    Q_INVOKABLE void setName(QString name);
    Q_INVOKABLE void setArtist(QString artist);
    Q_INVOKABLE void setAlbum(QString album);
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
