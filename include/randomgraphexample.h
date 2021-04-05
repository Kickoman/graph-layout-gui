#ifndef RANDOMGRAPHEXAMPLE_H
#define RANDOMGRAPHEXAMPLE_H

#include "igraph.h"

#include <QVector>

///
/// \brief Generates a random graph with the given number of
///        nodes and edges
///
class RandomGraphExample : public PositionedGraph
{
public:
    RandomGraphExample(int nodes, int edges, unsigned int seed = 0);

    int nodesCount() const override;
    int edgesCount() const override;
    PolymorphicTypes::Variant node(int index) const override;
    std::pair<int, int> edge(int index) const override;
    PolymorphicTypes::Variant edgeProperties(int index) const override;

    bool isAdjacent(int a, int b) const override;

    GraphGeometry::Point nodePosition(int index) const override;
    void setNodePosition(int index, GraphGeometry::Point position) override;

private:
    using AdjacencyRow = QVector<int>;
    using AdjacencyMatrix = QVector<AdjacencyRow>;
    using Edge = QPair<int, int>;
    using EdgeList = QVector<Edge>;

    void generateRandom(int N, int M, unsigned int seed = 0);
    bool addEdge(int a, int b);

    QVector<PolymorphicTypes::Variant> nodes;
    AdjacencyMatrix matrix;
    EdgeList edgeList;
    QVector<GraphGeometry::Point> positions;
};

#endif // RANDOMGRAPHEXAMPLE_H
