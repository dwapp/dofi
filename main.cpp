#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QProcess>

//QList<QByteArray> executeShellScript()
//{
//    QProcess process;
//    process.start("dmenu_path");
//    process.waitForFinished();

//    return process.readAll().split('/n');
//}

int main(int argc, char *argv[])
{
    //qputenv("QT_QPA_PLATFORM", "wayland");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/DLauncher/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
