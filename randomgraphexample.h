#ifndef RANDOMGRAPHEXAMPLE_H
#define RANDOMGRAPHEXAMPLE_H

#include "igraph.h"

#include <QVector>


class RandomGraphExample : public IGraph
{
public:
    RandomGraphExample(int nodes, int edges);

    int nodesCount() const override;
    int edgesCount() const;
    QVariant node(int index) const;
    QPair<int, int> edge(int index) const;
    QVariant edgeProperties(int index) const;

    bool isAdjacent(int a, int b) const;

private:
    using AdjacencyRow = QVector<int>;
    using AdjacencyMatrix = QVector<AdjacencyRow>;
    using Edge = QPair<int, int>;
    using EdgeList = QVector<Edge>;

    void generateRandom(int N, int M);
    bool addEdge(int a, int b);

    QVector<QVariant> nodes;
    AdjacencyMatrix matrix;
    EdgeList edgeList;
};

#endif // RANDOMGRAPHEXAMPLE_H
