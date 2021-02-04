#include "randomgraphexample.h"
#include <QDebug>
#include <ctime>

RandomGraphExample::RandomGraphExample(int nodes, int edges)
{
    generateRandom(nodes, edges);
}

int RandomGraphExample::nodesCount() const
{
    return nodes.size();
}

int RandomGraphExample::edgesCount() const
{
    return edgeList.size();
}

QVariant RandomGraphExample::node(int index) const
{
    return nodes.at(index);
}

QPair<int, int> RandomGraphExample::edge(int index) const
{
    return edgeList.at(index);
}

QVariant RandomGraphExample::edgeProperties(int index) const
{
    Q_UNUSED(index)
    return QVariant();
}

bool RandomGraphExample::isAdjacent(int a, int b) const
{
    return matrix[a][b];
}

void RandomGraphExample::generateRandom(int N, int M)
{
    matrix.resize(N);
    for (auto &line : matrix)
        line.resize(N);

    if (M < N * (N - 1) / 2)
    {
        auto _seed = static_cast<unsigned int>(time(nullptr));
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
        for (auto &line : matrix)
            line.fill(1);
    }
}

bool RandomGraphExample::addEdge(int a, int b)
{
    if (!matrix[a][b])
    {
        matrix[a][b] = matrix[b][a] = 1;
        return true;
    }
    return false;
}
