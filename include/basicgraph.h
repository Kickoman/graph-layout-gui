#ifndef BASICGRAPH_H
#define BASICGRAPH_H

#include "igraph.h"
#include "2d/point.h"
#include <QVector>
#include <QMutex>
#include <QObject>
#include <memory>

using PointType = GraphGeometry::D2::Point;


class Graph
{
public:
    Graph();

    void clearEdges();

    int nodesCount() const;
    int edgesCount() const;
    QPair<int, int> edge(int index) const;

    bool isAdjacent(int a, int b) const;

    void setNodeValue(int nodeIndex, const QString &text);
    void setNodesCount(int nodesCount);
    void connectNodes(int a, int b);

    PointType nodePosition(int index) const;
    void setNodePosition(int index, PointType);

    QVariant node(int index) const;
    QVariant edgeProperties(int index) const;
private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPair<int, int>> edgeList;
    QVector<QPair<QString, PointType>> nodeList;

    // Extension
    QVector<PointType> nodePositions;
};


class GraphAdapter : public IGraph<PointType>
{
public:
    explicit GraphAdapter(Graph *graph) : graph(graph) {}

    int nodesCount() const override {
        return graph->nodesCount();
    }
    int edgesCount() const override {
        return graph->edgesCount();
    }
    std::pair<int, int> edge(int index) const override {
        return graph->edge(index);
    }
    PointType nodePosition(int index) const override {
        return graph->nodePosition(index);
    }
    void setNodePosition(int index, PointType point) override {
        graph->setNodePosition(index, point);
    }
    void flush() override {
        callback();
    }
    void setCallback(std::function<void()>& cb) {
        callback = std::move(cb);
    }
private:
    Graph *graph = nullptr;
    std::function<void()> callback;
};
using GraphAdapterPtr = std::shared_ptr<GraphAdapter>;


class GraphKeeper : public QObject {
    Q_OBJECT
public:
    GraphKeeper() = default;
    explicit GraphKeeper(Graph &graph) : graph(std::move(graph))
    {}

    GraphAdapterPtr GetWriteAdapter() {
        auto adapter = std::make_shared<GraphAdapter>(&graph);
        std::function<void()> callback = [this]{
            emit this->updated();
        };
        adapter->setCallback(callback);
        return adapter;
    }

    const Graph *getGraph() const {
        return &graph;
    }

    void setGraph(Graph &graph) {
        this->graph = graph;
        emit updated();
    }

signals:
    void updated();

private:
    Graph graph;
};
using GraphKeeperPtr = std::shared_ptr<GraphKeeper>;

#endif // BASICGRAPH_H
