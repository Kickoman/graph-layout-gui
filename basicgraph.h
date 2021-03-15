#ifndef BASICGRAPH_H
#define BASICGRAPH_H

#include "igraph.h"

class BasicGraph : public IGraph
{
public:
    BasicGraph();

    int nodesCount() const override;
    int edgesCount() const override;
    QVariant node(int index) const override;
    QPair<int, int> edge(int index) const override;
    QVariant edgeProperties(int index) const override;

    bool isAdjacent(int a, int b) const override;

    void setNodeValue(int nodeIndex, const QString &text);
    void setNodesCount(int nodesCount);
    void connectNodes(int a, int b);

private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPair<int, int>> edgeList;
    QVector<QString> nodeList;
};

#endif // BASICGRAPH_H
