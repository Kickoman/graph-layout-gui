#include "basicgraph.h"

BasicGraph::BasicGraph()
= default;

int BasicGraph::nodesCount() const
{
    return nodeList.size();
}

int BasicGraph::edgesCount() const
{
    return edgeList.size();
}

PolymorphicTypes::Variant BasicGraph::node(int index) const
{
    return PolymorphicTypes::Variant(nodeList.at(index).toStdString());
}

std::pair<int, int> BasicGraph::edge(int index) const
{
    auto edge = edgeList.at(index);
    return {edge.first, edge.second};
}

PolymorphicTypes::Variant BasicGraph::edgeProperties(int index) const
{
    Q_UNUSED(index)
    return PolymorphicTypes::Variant();
}

bool BasicGraph::isAdjacent(int a, int b) const
{
    return adjacencyMatrix[a][b] == 1;
}

void BasicGraph::setNodeValue(int nodeIndex, const QString &text)
{
    nodeList[nodeIndex] = text;
}

void BasicGraph::setNodesCount(int nodesCount)
{
    nodeList.resize(nodesCount);
    positions.resize(nodesCount);
    adjacencyMatrix.resize(nodesCount);
    for (auto &row : adjacencyMatrix)
        row.resize(nodesCount);
}

void BasicGraph::connectNodes(int a, int b)
{
    adjacencyMatrix[a][b] = 1;
    adjacencyMatrix[b][a] = 1;

    if (a > b)
        std::swap(a, b);
    if (!edgeList.contains({a, b}))
        edgeList.push_back({a, b});
}

GraphGeometry::Point BasicGraph::nodePosition(int index) const
{
    return positions[index];
}

void BasicGraph::setNodePosition(int index, GraphGeometry::Point position)
{
    positions[index] = position;
}
