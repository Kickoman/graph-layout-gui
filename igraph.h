#ifndef IGRAPH_H
#define IGRAPH_H

#include <QVariant>
// TODO: Implement

class IGraph
{
public:
    virtual ~IGraph() = default;
    virtual int nodesCount() const = 0;
    virtual int edgesCount() const = 0;
    virtual QVariant node(int index) const = 0;
    virtual QPair<int, int> edge(int index) const = 0;
    virtual QVariant edgeProperties(int index) const = 0;

    virtual bool isAdjacent(int a, int b) const = 0;
};

#endif // IGRAPH_H
