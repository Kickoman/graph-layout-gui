#include "randomgraphexample.h"
#include <QDebug>
#include <ctime>

RandomGraphExample::RandomGraphExample(int nodes, int edges, unsigned int seed)
{
    generateRandom(nodes, edges, seed);
}

int RandomGraphExample::nodesCount() const
{
    return nodes.size();
}

int RandomGraphExample::edgesCount() const
{
    return edgeList.size();
}

PolymorphicTypes::Variant RandomGraphExample::node(int index) const
{
    return nodes.at(index);
}

std::pair<int, int> RandomGraphExample::edge(int index) const
{
    auto edge = edgeList.at(index);
    return {edge.first, edge.second};
}

PolymorphicTypes::Variant RandomGraphExample::edgeProperties(int index) const
{
    Q_UNUSED(index)
    return {};
}

bool RandomGraphExample::isAdjacent(int a, int b) const
{
    return matrix[a][b];
}

GraphGeometry::Point RandomGraphExample::nodePosition(int index) const
{
    return positions[index];
}

void RandomGraphExample::setNodePosition(int index, GraphGeometry::Point position)
{
    positions[index] = position;
}

void RandomGraphExample::generateRandom(int N, int M, unsigned int seed)
{
    nodes.resize(N);
    positions.resize(N);
    for (int i = 0; i < N; ++i) nodes[i] = PolymorphicTypes::Variant(i);

    matrix.resize(N);
    for (auto &line : matrix)
        line.resize(N);

    if (M < N * (N - 1) / 2)
    {
        unsigned int _seed = seed == 0 ? static_cast<unsigned int>(time(nullptr)) : seed;
        qDebug() << "seed:" << _seed;
        srand(_seed);

        while (M)
        {
            int a = rand() % N;
            int b = rand() % N;
            M -= addEdge(a, b);
        }
    }
    else
    {
        qDebug() << "Full graph";
        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j)
                addEdge(i, j);
    }
}

bool RandomGraphExample::addEdge(int a, int b)
{
    if (!matrix[a][b] && a != b)
    {
        matrix[a][b] = matrix[b][a] = 1;
        edgeList.append(qMakePair(a, b));
        return true;
    }
    return false;
}
