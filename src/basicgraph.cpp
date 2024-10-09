#include "basicgraph.h"
#include <QVariant>


Graph::Graph()
= default;

int Graph::nodesCount() const
{
    return nodeList.size();
}

int Graph::edgesCount() const
{
    return edgeList.size();
}

void Graph::clearEdges() {
    edgeList.clear();
    for (auto& row : adjacencyMatrix) {
        row.fill(0);
    }
}

QVariant Graph::node(int index) const
{
    return nodeList.at(index).first;
}

QPair<int, int> Graph::edge(int index) const
{
    return edgeList.at(index);
}

QVariant Graph::edgeProperties(int index) const
{
    Q_UNUSED(index)
    return QVariant();
}

bool Graph::isAdjacent(int a, int b) const
{
    return adjacencyMatrix[a][b] == 1;
}

void Graph::setNodeValue(int nodeIndex, const QString &text)
{
    nodeList[nodeIndex].first = text;
}

void Graph::setNodesCount(int nodesCount)
{
    nodeList.resize(nodesCount);
    adjacencyMatrix.resize(nodesCount);
    for (auto &row : adjacencyMatrix)
        row.resize(nodesCount);
}

void Graph::connectNodes(int a, int b)
{
    adjacencyMatrix[a][b] = 1;
    adjacencyMatrix[b][a] = 1;

    if (a > b)
        std::swap(a, b);
    if (!edgeList.contains({a, b}))
        edgeList.push_back({a, b});
}

PointType Graph::nodePosition(int index) const {
    return nodeList[index].second;
}

void Graph::setNodePosition(int index, PointType point) {
    nodeList[index].second = point;
}
