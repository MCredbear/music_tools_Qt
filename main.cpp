#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "editor.h"
#include "toast.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    Editor editor;
    Toast toast;
    editor.readFile("/home/redbear/堀江晶太 Evan Call - Sincerely (off vocal).flac");
    engine.rootContext()->setContextProperty("editor", &editor);
    engine.rootContext()->setContextProperty("toast", &toast);
    engine.addImageProvider("coverImageProvider", editor.coverImageProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
