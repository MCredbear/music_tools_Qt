#include "toast.h"

Toast::Toast(QObject *parent)
    : QObject{parent}
{

}

void Toast::sendToast(QString text)
{
    emit toastSended(text);
}