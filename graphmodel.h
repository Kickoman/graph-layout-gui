#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QMutex>
#include "igraph.h"
#include "graphcalculator.h"

class GraphLayout : public QObject
{
    Q_OBJECT
public:
    GraphLayout(IGraph *graph);

    Q_INVOKABLE
    int nodesCount() const;

    Q_INVOKABLE
    int edgesCount() const;

    Q_INVOKABLE
    QVariant node(int index) const;

    Q_INVOKABLE
    QPair<int, int> edge(int index) const;

    Q_INVOKABLE
    QVariant edgeProperties(int index) const;

    Q_INVOKABLE
    double getNodeXPosition(int index) const;

    Q_INVOKABLE
    double getNodeYPosition(int index) const;

    Q_INVOKABLE
    void recalculatePositions();

    Q_INVOKABLE
    void setGraphCalculatorConfig(GraphCalculatorConfig config);

signals:
    void positionsUpdated();
    void positionUpdated(int nodeIndex);

private:
    mutable QMutex positionsLock;
    QVector<QPointF> positions;
    GraphCalculatorConfig config;
    IGraph *graph;
};

#endif // GRAPHMODEL_H
