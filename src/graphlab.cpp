#include "graphlab.h"
#include "randomgraphexample.h"
#include "basicgraphparser.h"
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
}

void GraphLab::setGraph(const QString &graphDescription)
{
    IGraph* temp = graph;
    BasicGraphParser::parseGraph(graphDescription, &graph);

    if (graphLayout == nullptr)
        graphLayout = new GraphLayout(graph);
    else
        graphLayout->setGraph(graph);

    delete temp;
}

GraphLayout *GraphLab::getGraphLayout() const
{
    return graphLayout;
}
