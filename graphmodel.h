#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QMutex>
#include <QAbstractListModel>
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
    QVariant edgeQml(int index) const;

    Q_INVOKABLE
    QVariant edgeProperties(int index) const;

    Q_INVOKABLE
    double getNodeXPosition(int index) const;

    Q_INVOKABLE
    double getNodeYPosition(int index) const;

    Q_INVOKABLE
    void setNodeXPosition(int index, double x);

    Q_INVOKABLE
    void setNodeYPosition(int index, double y);

    Q_INVOKABLE
    void recalculatePositions();

    Q_INVOKABLE
    void setRandomPositions();

    Q_INVOKABLE
    void setGraphCalculatorConfig(const GraphCalculatorConfig &config);

    Q_INVOKABLE
    void setRepulsiveForce(const QString &formula);

    Q_INVOKABLE
    void setAttractiveForce(const QString &formula);

    Q_INVOKABLE
    void setNodeSize(int width, int height);

    Q_INVOKABLE
    QVariant getNodesModel();

    Q_INVOKABLE
    QVariant getEdgesModel();
signals:
    void positionsUpdated();
    void positionUpdated(int nodeIndex);
    void modelUpdated();

private slots:
    void onGraphChanged();

private:
    mutable QMutex positionsLock;
    QVector<QPointF> positions;
    GraphCalculatorConfig config;
    IGraph *graph;

    QAbstractListModel *nodesModel;
    QAbstractListModel *edgesModel;
};

#endif // GRAPHMODEL_H
