#include "file_manager.h"

file_manager::file_manager(QObject *parent)
    : QObject{parent}
{
}

int file_manager::readDir(QString path)
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

bool file_manager::isFile(int index)
{
    return fileInfoList.at(index).isFile();
}

QString file_manager::name(int index)
{
    return fileInfoList.at(index).fileName();
}

QString file_manager::modifiedTime(int index)
{
    return fileInfoList.at(index).lastModified().toString("yyyy MM dd hh:mm:ss");
}