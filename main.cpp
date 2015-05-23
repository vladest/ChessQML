#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chesscontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChessController>("Chess", 1, 0, "ChessController");

    ChessController chessController;

    QQmlApplicationEngine engine;
    QQmlContext *qmlcontext = engine.rootContext();
    if (!qmlcontext) {
        qWarning() << "Cannot get QML context";
        return 0;
    }
    qmlcontext->setContextProperty("chessController", &chessController);
    engine.load(QUrl(QStringLiteral("qml/main.qml")));

    return app.exec();
}
