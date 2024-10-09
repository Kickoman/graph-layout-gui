#ifndef BASICGRAPH_H
#define BASICGRAPH_H

#include "igraph.h"
#include "2d/point.h"
#include <QVector>
#include <QMutex>
#include <QObject>
#include <memory>
#include <functional>


using PointType = GraphGeometry::D2::Point;


/**
 * @brief Basic positioned graph
 * No Qt specifics here, it can be any other class.
 *
 */
class Graph
{
public:
    Graph();

    /**
     * @brief Clears all edges from graph
     *
     */
    void clearEdges();

    /**
     * @brief Getter for the number of nodes in graph
     *
     * @return int Total number of nodes
     */
    int nodesCount() const;

    /**
     * @brief Getter for the number of edges in graph
     *
     * @return int Total number of edges
     */
    int edgesCount() const;

    /**
     * @brief Getter for the information abouth the edge
     *
     * @param index Edge index (between 0 and the total number of edges)
     * @return QPair<int, int> Pair of indices (start and finish node)
     */
    QPair<int, int> edge(int index) const;

    /**
     * @brief Checks whether two nodes are adjacent
     *
     * @param a First node index
     * @param b Second node index
     * @return true Nodes are adjacent
     * @return false Nodes are not adjacent
     */
    bool isAdjacent(int a, int b) const;

    /**
     * @brief Set value for the node
     *
     * @param nodeIndex Node index
     * @param text Node value
     */
    void setNodeValue(int nodeIndex, const QString &text);

    /**
     * @brief Set new number of nodes
     *
     * If new number of nodes is smaller than the previous one,
     * the nodes with the largest indices will be truncated.
     *
     * @param nodesCount New number of nodes
     */
    void setNodesCount(int nodesCount);

    /**
     * @brief Make two nodes adjacent (connect them with an edje)
     *
     * @param a First node index
     * @param b Second node index
     */
    void connectNodes(int a, int b);

    /**
     * @brief Retrieves the position of the node
     *
     * @param index Node index
     * @return PointType Node coordinates
     */
    PointType nodePosition(int index) const;

    /**
     * @brief Set the position for the node
     *
     * @param index Node index
     * @param point PointType New node position
     */
    void setNodePosition(int index, PointType point);

    /**
     * @brief Retrieves node value
     *
     * @param index Node index
     * @return QVariant Node value
     */
    QVariant node(int index) const;

    /**
     * @brief Retrieves edge properties
     *
     * @param index Edge index
     * @return QVariant Edge properties
     */
    QVariant edgeProperties(int index) const;
private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPair<int, int>> edgeList;
    QVector<QPair<QString, PointType>> nodeList;

    // Extension
    QVector<PointType> nodePositions;
};


/**
 * @brief Positioned adapter for the graph calculator
 *
 */
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

    Graph *getGraph() {
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
