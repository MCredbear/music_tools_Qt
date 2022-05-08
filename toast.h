#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QDebug>

class Toast : public QObject
{
    Q_OBJECT
public:
    explicit Toast(QObject *parent = nullptr);
    Q_INVOKABLE void sendToast(QString text);
signals:
    void toastSended(QString text);
};

#endif // TOAST_H
