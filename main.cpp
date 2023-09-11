#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    //qputenv("QT_QPA_PLATFORM", "wayland");

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/DLauncher/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
