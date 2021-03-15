#include "graphlab.h"
#include "randomgraphexample.h"

#include <QTimer>

GraphLab::GraphLab(QObject *parent) : QObject(parent)
{

}

void GraphLab::generateGraph(int nodes, int edges)
{
    graph = new RandomGraphExample(nodes, edges);
    graphLayout = new GraphLayout(graph);
    graphLayout->setRandomPositions();
    emit layoutReady();
//    emit graphLayout->modelUpdated();

//    QTimer::singleShot(500, graphLayout, [this]{graphLayout->setRandomPositions();});
}

void GraphLab::setGraph(const QString &graphDescription)
{
    Q_UNUSED(graphDescription)
}

GraphLayout *GraphLab::getGraphLayout() const
{
    return graphLayout;
}
