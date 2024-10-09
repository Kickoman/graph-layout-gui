#include "graphlab.h"
#include "basicgraph.h"
#include "graphlayout.h"
#include "basicgraphparser.h"
#include <QTimer>
#include <QDebug>


GraphLab::GraphLab(QObject *parent)
    : QObject(parent)
    , graphKeeper(std::make_shared<GraphKeeper>())
{}

void fillRandomGraph(Graph* graph, const int n, int m, const unsigned int seed)
{
    graph->clearEdges();
    graph->setNodesCount(0);
    graph->setNodesCount(n);
    for (int i = 0; i < n; ++i) {
        graph->setNodeValue(i, QString::number(i));
    }
    if (m < n * (n - 1) / 2)
    {
        unsigned int _seed = seed == 0 ? static_cast<unsigned int>(time(nullptr)) : seed;
        qDebug() << "seed:" << _seed;
        srand(_seed);

        while (m)
        {
            int a = rand() % n;
            int b = rand() % n;
            if (!graph->isAdjacent(a, b)) {
                graph->connectNodes(a, b);
                --m;
            }
        }
    }
    else
    {
        qDebug() << "Full graph";
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                graph->connectNodes(i, j);
            }
        }
    }
}

void GraphLab::generateGraph(int nodes, int edges)
{
    Graph graph;
    fillRandomGraph(&graph, nodes, edges, 0);
    graphKeeper->setGraph(graph);
    graphLayout = new GraphLayout(graphKeeper);
    graphLayout->setRandomPositions();
    emit layoutReady();
}

void GraphLab::setGraph(const QString &graphDescription)
{
    Graph graph;
    BasicGraphParser::parseGraph(graphDescription, graph);
    graphKeeper->setGraph(graph);

    if (graphLayout == nullptr)
        graphLayout = new GraphLayout(graphKeeper);
    else
        graphLayout->setGraphKeeper(graphKeeper);
}

GraphLayout *GraphLab::getGraphLayout() const
{
    return graphLayout;
}
