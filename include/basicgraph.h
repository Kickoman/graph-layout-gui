#ifndef BASICGRAPH_H
#define BASICGRAPH_H

#include "igraph.h"
#include <QVector>

class BasicGraph : public PositionedGraph
{
public:
    BasicGraph();

    int nodesCount() const override;
    int edgesCount() const override;
    PolymorphicTypes::Variant node(int index) const override;
    std::pair<int, int> edge(int index) const override;
    PolymorphicTypes::Variant edgeProperties(int index) const override;

    bool isAdjacent(int a, int b) const override;

    void setNodeValue(int nodeIndex, const QString &text);
    void setNodesCount(int nodesCount);
    void connectNodes(int a, int b);

    GraphGeometry::Point nodePosition(int index) const override;
    void setNodePosition(int index, GraphGeometry::Point position) override;

private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPair<int, int>> edgeList;
    QVector<QString> nodeList;
    QVector<GraphGeometry::Point> positions;
};

#endif // BASICGRAPH_H
