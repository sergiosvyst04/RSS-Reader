#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <RssModel.hpp>
#include <QQmlContext>
#include <QQuickStyle>
#include <ApplicationViewModel.hpp>


#define QML_REGISTER_TYPE_HELPER(Class) qmlRegisterType<Class>(uri, versionMajor, versionMinor, #Class)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");


    qmlRegisterType<RssModel>("Rss", 1, 0, "RssModel");
    qRegisterMetaType<ApplicationViewModel*>("ApplicationViewModel*");

//    int versionMajor = 1;
//    int versionMinor = 0;
//    QML_REGISTER_TYPE_HELPER(RssModel);
    qmlRegisterType<RequestSender>("Request", 1, 0, "RequestSender");


    qmlRegisterSingletonType<ApplicationViewModel>("ApplicationVM", 1, 0, "ApplicationViewModel", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        engine->setObjectOwnership(ApplicationViewModel::Instance(), QQmlEngine::CppOwnership);
        return ApplicationViewModel::Instance();
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
