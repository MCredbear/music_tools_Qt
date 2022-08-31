#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QObject>
#include <QFileInfoList>
#include <QDateTime>
#include <QDir>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    QFileInfoList fileInfoList;
    Q_INVOKABLE int readDir(QString path); //返回文件数量
    Q_INVOKABLE bool isFile(int index);
    Q_INVOKABLE QString name(int index);
    Q_INVOKABLE QString modifiedTime(int index);


signals:

};

#endif // FILE_MANAGER_H
