#ifndef RANDOMGRAPHEXAMPLE_H
#define RANDOMGRAPHEXAMPLE_H

#include "igraph.h"

#include <QVector>


class RandomGraphExample : public IGraph
{
public:
    RandomGraphExample(int nodes, int edges, unsigned int seed = 0);

    int nodesCount() const override;
    int edgesCount() const override;
    QVariant node(int index) const override;
    QPair<int, int> edge(int index) const override;
    QVariant edgeProperties(int index) const override;

    bool isAdjacent(int a, int b) const override;

private:
    using AdjacencyRow = QVector<int>;
    using AdjacencyMatrix = QVector<AdjacencyRow>;
    using Edge = QPair<int, int>;
    using EdgeList = QVector<Edge>;

    void generateRandom(int N, int M, unsigned int seed = 0);
    bool addEdge(int a, int b);

    QVector<QVariant> nodes;
    AdjacencyMatrix matrix;
    EdgeList edgeList;
};

#endif // RANDOMGRAPHEXAMPLE_H
