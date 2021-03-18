#include <QApplication>
#include <QQuickView>
#include <QMessageBox>
#include <QQmlError>
#include <QQmlContext>
#include <QQmlEngine>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QInputDialog>
#include <QTimer>
#include <ctime>

#include "graphlab.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Graph lab");

    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption seedOption(QStringList() << "s" << "seed", "Specify seed", "seed", "0");
    QCommandLineOption graphOption(QStringList() << "f" << "file", "Set graph description", "graph");
    parser.addOption(seedOption);
    parser.addOption(graphOption);
    parser.process(a);

    unsigned seed = parser.value(seedOption).toUInt();
    srand(seed > 0 ? seed : unsigned(time(nullptr)));

    QString graphDescription;
    if (parser.isSet(graphOption))
    {
        QFile file(parser.value(graphOption));
        if (file.open(QIODevice::ReadOnly))
        {
            graphDescription = file.readAll();
        }
    }

    auto *program = new GraphLab();

    if (!graphDescription.isEmpty())
        program->setGraph(graphDescription);

    QQuickView view;
    view.engine()->addImportPath("qrc:/graph-layout/GraphLayout");
    view.rootContext()->setContextProperty("graphModel", program);
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.showMaximized();

    qDebug() << view.engine()->importPathList();

    return a.exec();
}
