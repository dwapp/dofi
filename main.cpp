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
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    const QUrl url(u"qrc:/qt/qml/Dofi/Main.qml"_qs);
#else
    const QUrl url(u"qrc:/Dofi/Main.qml"_qs);
#endif
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
