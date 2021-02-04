#include "graphmodel.h"

#include <QThreadPool>

GraphLayout::GraphLayout(IGraph *graph)
    : graph(graph)
{}

int GraphLayout::nodesCount() const
{
    return graph->nodesCount();
}

int GraphLayout::edgesCount() const
{
    return graph->edgesCount();
}

QVariant GraphLayout::node(int index) const
{
    return graph->node(index);
}

QPair<int, int> GraphLayout::edge(int index) const
{
    return graph->edge(index);
}

QVariant GraphLayout::edgeProperties(int index) const
{
    return graph->edgeProperties(index);
}

double GraphLayout::getNodeXPosition(int index) const
{
    bool indexOkay = index > -1 && index < nodesCount();
    return indexOkay ? positions[index].x() : -1;
}

double GraphLayout::getNodeYPosition(int index) const
{
    bool indexOkay = index > -1 && index < nodesCount();
    return indexOkay ? positions[index].y() : -1;
}

void GraphLayout::recalculatePositions()
{
    auto pool = QThreadPool::globalInstance();
    auto calc = new GraphCalculator(graph, positions, positionsLock, config);
    calc->setAutoDelete(true);
    connect(calc, &GraphCalculator::finished, this, &GraphLayout::positionsUpdated);
    pool->start(calc);
}

void GraphLayout::setGraphCalculatorConfig(GraphCalculatorConfig config)
{
    this->config = config;
}
