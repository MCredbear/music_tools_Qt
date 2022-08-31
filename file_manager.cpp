#include "file_manager.h"

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{
}

int FileManager::readDir(QString path)
{
    fileInfoList.clear();
    QDir dir(path);
    QStringList nameFilter;
    nameFilter << "*.[Mm][Pp]3"
               << "*.[Ff][Ll][Aa][Cc]"
               << "[Mm]4[Aa]"
               << "[Ww][Aa][Vv]"
               << "[Oo][Gg][Gg]";
    fileInfoList.append(dir.entryInfoList(QDir::Dirs));
    fileInfoList.append(dir.entryInfoList(nameFilter));

    return fileInfoList.length();
}

bool FileManager::isFile(int index)
{
    return fileInfoList.at(index).isFile();
}

QString FileManager::name(int index)
{
    return fileInfoList.at(index).fileName();
}

QString FileManager::modifiedTime(int index)
{
    return fileInfoList.at(index).lastModified().toString("yyyy MM dd hh:mm:ss");
}