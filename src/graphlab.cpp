#include "graphlab.h"
#include "randomgraphexample.h"
#include "basicgraphparser.h"
#include "forcedgraphcalculator.h"
#include "kfunction.h"
#include <QTimer>

GraphLab::GraphLab(QObject *parent) : QObject(parent)
{
    calculator = new ForcedGraphCalculator();
}

void GraphLab::generateGraph(int nodes, int edges)
{
    graph = new RandomGraphExample(nodes, edges);
    graphLayout = new GraphLayout(graph);
    graphLayout->setGraphCalculator(calculator);
    graphLayout->setRandomPositions();
    emit layoutReady();
}

void GraphLab::setGraph(const QString &graphDescription)
{
    PositionedGraph* temp = graph;
    BasicGraphParser::parseGraph(graphDescription, &graph);

    if (graphLayout == nullptr)
    {
        graphLayout = new GraphLayout(graph);
        graphLayout->setGraphCalculator(calculator);
    }
    else
        graphLayout->setGraph(graph);

    delete temp;
}

GraphLayout *GraphLab::getGraphLayout() const
{
    return graphLayout;
}

void GraphLab::setAttractiveForce(const QString &force)
{
    config.attractiveForce = Function<double>(force.toStdString());
}

void GraphLab::setRepulsiveForce(const QString &force)
{
    config.repulsiveForce = Function<double>(force.toStdString());
}

void GraphLab::setFrameSize(int width, int height)
{
    config.frameWidth = width;
    config.frameHeight = height;
}

void GraphLab::setNodeSize(int width, int height)
{
    config.nodeWidth = width;
    config.nodeHeight = height;
}

void GraphLab::recalculatePositions()
{
    calculator->setConfig(config);
    calculator->setForces(forces);
    graphLayout->recalculatePositions();
}
