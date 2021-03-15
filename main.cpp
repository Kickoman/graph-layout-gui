#include <QApplication>
#include <QQuickView>
#include <QMessageBox>
#include <QQmlError>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QInputDialog>
#include <QTimer>

#include "randomgraphexample.h"
#include "graphlayout.h"
#include "starter.h"

#include "graphlab.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Graph lab");

    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption seedOption(QStringList() << "s" << "seed", "Specify seed", "seed", "0");
    parser.addOption(seedOption);
    parser.process(a);

    unsigned seed = parser.value(seedOption).toUInt();
    srand(seed > 0 ? seed : unsigned(time(nullptr)));

    auto *program = new GraphLab();
    QQuickView view;
    view.rootContext()->setContextProperty("graphModel", program);
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.showMaximized();

    return a.exec();
}
