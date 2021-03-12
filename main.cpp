#include <QApplication>
#include <QQuickView>
#include <QMessageBox>
#include <QQmlError>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QInputDialog>

#include "randomgraphexample.h"
#include "graphlayout.h"
#include "starter.h"

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

#ifndef WASM_BUILD
    int nodes = QInputDialog::getInt(nullptr, "Nodes", "Nodes", 5, 0, 1000);
    int edges = QInputDialog::getInt(nullptr, "Edges", "Edges", 5, 0, 1000);

    qDebug() << "Generating base graph";
    auto graph = new RandomGraphExample(nodes, edges, seed);
    qDebug() << "Graph info. Nodes:" << graph->nodesCount() << "; edges:" << graph->edgesCount();
    qDebug() << "Creating a model";
    auto model = new GraphLayout(graph);
    model->setRandomPositions();

    qDebug() << "Creating view...";
    QQuickView view;
    qDebug() << "Inserting a model into the view...";
    view.rootContext()->setContextProperty("graphModel", model);
    view.setSource(QUrl("qrc:/qml/main.qml"));
    if (view.status() == QQuickView::Status::Error)
    {
        auto errors = view.errors();
        QString errorsString;
        for (const auto &error : qAsConst(errors))
            errorsString.append(QString("%1\n").arg(error.toString()));
        QMessageBox::critical(nullptr,
                              "Critical error",
                              "Can't start view. Errors:\n" + errorsString);
        return -1;
    }
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.show();
#else
    Starter s(seed);
    s.start();
#endif
    return a.exec();
}
