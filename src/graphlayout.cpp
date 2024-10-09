#include "graphlayout.h"
#include "2d/point.h"
#include "graphcalculator.h"
#include "graphnodesproxymodel.h"
#include "graphlineproxymodel.h"
#include "basicgraph.h"

#include <QtConcurrent>
#include <memory>

GraphLayout::GraphLayout(std::shared_ptr<GraphKeeper> graph)
    : graphKeeper(graph)
    , graphAdapter(graph->GetWriteAdapter())
    , nodesModel(nullptr)
    , edgesModel(nullptr)
{
    connect(graphKeeper.get(), &GraphKeeper::updated, this, &GraphLayout::positionsUpdated);
}

int GraphLayout::nodesCount() const
{
    return graphKeeper->getGraph()->nodesCount();
}

int GraphLayout::edgesCount() const
{
    return graphKeeper->getGraph()->edgesCount();
}

QVariant GraphLayout::node(int index) const
{
    return graphKeeper->getGraph()->node(index);
}

QPair<int, int> GraphLayout::edge(int index) const
{
    return graphKeeper->getGraph()->edge(index);
}

QVariant GraphLayout::edgeProperties(int index) const
{
    return graphKeeper->getGraph()->edgeProperties(index);
}

double GraphLayout::getNodeXPosition(int index) const
{
    bool indexOkay = index > -1 && index < nodesCount();
    return indexOkay ? graphKeeper->getGraph()->nodePosition(index).x() : -1.;
}

double GraphLayout::getNodeYPosition(int index) const
{
    bool indexOkay = index > -1 && index < nodesCount();
    return indexOkay ? graphKeeper->getGraph()->nodePosition(index).y() : -1.;
}

void GraphLayout::setNodeXPosition(int index, double x)
{
    if (!qFuzzyCompare(getNodeXPosition(index), x))
    {
        graphKeeper->getGraph()->setNodePosition(index, GraphGeometry::D2::Point(x, getNodeYPosition(index)));
        emit positionUpdated(index);
    }
}

void GraphLayout::setNodeYPosition(int index, double y)
{
    if (!qFuzzyCompare(getNodeYPosition(index), y))
    {
        graphKeeper->getGraph()->setNodePosition(index, GraphGeometry::D2::Point(getNodeXPosition(index), y));
        emit positionUpdated(index);
    }
}

void GraphLayout::recalculatePositions()
{
    // If something is being executed, wait for finish
    calculator.requestStop();
    if (executionThread.joinable())
    {
        executionThread.join();
    }

    calculator.setGraph(graphKeeper->GetWriteAdapter());
    calculator.setConfig(config);
    executionThread = std::thread(&GraphCalculator::run, &calculator);
}

void GraphLayout::setRandomPositions()
{
    auto area = std::max(config.nodeHeight * nodesCount(), config.nodeWidth * nodesCount());
    const auto n = nodesCount();
    for (int i = 0; i < n; ++i)
    {
        double x = rand() % int(area);
        double y = rand() % int(area);
        graphKeeper->getGraph()->setNodePosition(i, GraphGeometry::D2::Point(x, y));
    }
    emit positionsUpdated();
}

void GraphLayout::setGraphCalculatorConfig(const GraphCalculatorConfig &config)
{
    this->config = config;
}

void GraphLayout::setRepulsiveForce(const QString &formula)
{
    this->config.repulsiveForce = formula.toStdString();
}

QString GraphLayout::getRepulsiveForce() const
{
    // TODO: implement kfunction -> back to string
    return QString("Repulsive formula is not implemented yet");
}

void GraphLayout::setAttractiveForce(const QString &formula)
{
    this->config.attractiveForce = formula.toStdString();
}

QString GraphLayout::getAttractiveForce() const
{
    // TODO: implement kfunction -> back to string
    return QString("Attractive formula is not implemented yet");
}

void GraphLayout::setEdgesRepulsiveForce(const QString &formula)
{
    this->config.edgesRepulsiveForce = formula.toStdString();
}

void GraphLayout::setLinesRepulsiveForce(const QString &formula)
{
    this->config.linesRepulsiveForce = formula.toStdString();
}

void GraphLayout::setNodeSize(int width, int height)
{
    this->config.nodeWidth = width;
    this->config.nodeHeight = height;
}

void GraphLayout::setFrameSize(int width, int height)
{
    this->config.frameWidth = width;
    this->config.frameHeight = height;
}

QVariant GraphLayout::getNodesModel()
{
    if (!nodesModel)
    {
        nodesModel = new GraphNodesProxyModel(this);
    }
    return QVariant::fromValue(nodesModel);
}

QVariant GraphLayout::getEdgesModel()
{
    if (!edgesModel)
    {
        edgesModel = new GraphLineProxyModel(this);
    }
    return QVariant::fromValue(edgesModel);
}

void GraphLayout::setGraphKeeper(std::shared_ptr<GraphKeeper> graph)
{
    this->graphKeeper = graph;
    connect(graphKeeper.get(), &GraphKeeper::updated, this, &GraphLayout::positionsUpdated);
    emit modelUpdated();
}

void GraphLayout::onGraphChanged()
{
    setRandomPositions();
}
