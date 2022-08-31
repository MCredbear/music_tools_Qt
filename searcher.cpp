#include "searcher.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

Searcher::Searcher(QObject *parent)
    : QObject{parent}
{
}

QByteArray Searcher::search(QByteArray keyword, int offset)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QEventLoop eventloop;
    request.setUrl(QUrl("https://music.163.com/api/search/get"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("s=" + keyword + "&")
            .append("type=1&")
            .append("limit=10&")
            .append("offset=" + QByteArray::number(offset));
    QNetworkReply *reply = manager.post(request, postData);
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventloop, SLOT(quit()));
    eventloop.exec();
    QByteArrayList idList;
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jsonDocument.object().contains("result"))
        {
            QJsonArray songs = jsonDocument.object()["result"].toObject()["songs"].toArray();
            for (int i = 0; i < songs.count(); i++)
            {
                idList.append(QByteArray::number(songs[i].toObject()["id"].toInt()));
            }
            request.setUrl(QUrl("https://music.163.com/api/song/detail"));
            postData = "ids=[" + idList.join(",") + "]";
            reply = manager.post(request, postData);
            eventloop.exec();
            return reply->readAll();
        }
        else return "";
    }
    else return "";
}

QString Searcher::getLyric(int id)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QEventLoop eventloop;
    request.setUrl(QUrl("https://music.163.com/api/song/lyric?_nmclfl=1"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("id=" + QByteArray::number(id));
    postData.append("&tv=-1&lv=-1&rv=-1&kv=-1");
    QNetworkReply *reply = manager.post(request, postData);
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));
    eventloop.exec();
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        QString originalLyric = jsonDocument.object()["lrc"].toObject()["lyric"].toString() + "\n";
        QString translatedLyric = jsonDocument.object()["tlyric"].toObject()["lyric"].toString() + "\n";
        QString romanianLyric = jsonDocument.object()["romalrc"].toObject()["lyric"].toString() + "\n";
        return originalLyric + translatedLyric + romanianLyric;
    }
    else return "\0";
}
