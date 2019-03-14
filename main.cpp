#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <RssModel.hpp>
#include <QQmlContext>
#include <QQuickStyle>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");

    qmlRegisterType<RssModel>("Rss", 1, 0, "RssModel");
    qmlRegisterType<RequestSender>("Request", 1, 0, "RequestSender");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
