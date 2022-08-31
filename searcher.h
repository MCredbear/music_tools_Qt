#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>

class Searcher : public QObject
{
    Q_OBJECT
public:
    explicit Searcher(QObject *parent = nullptr);

    Q_INVOKABLE QByteArray search(QByteArray keyword, int offset);

    Q_INVOKABLE QString getLyric(int id);

signals:
    void songListChanged();
};



#endif // SEARCHER_H
