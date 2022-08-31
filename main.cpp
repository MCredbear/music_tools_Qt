#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "editor.h"
#include "file_manager.h"
#include "toast.h"
#include "searcher.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Editor editor;
    Toast toast;
    editor.toast = &toast;
    Searcher searcher;

    engine.rootContext()->setContextProperty("editor", &editor);
    engine.rootContext()->setContextProperty("toast", &toast);
    engine.rootContext()->setContextProperty("fileManager", new FileManager);
    engine.rootContext()->setContextProperty("searcher", &searcher);
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
