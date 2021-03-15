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

QVariant BasicGraph::node(int index) const
{
    return nodeList.at(index);
}

QPair<int, int> BasicGraph::edge(int index) const
{
    return edgeList.at(index);
}

QVariant BasicGraph::edgeProperties(int index) const
{
    Q_UNUSED(index)
    return QVariant();
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
