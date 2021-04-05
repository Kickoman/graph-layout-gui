#ifndef GRAPHLAB_H
#define GRAPHLAB_H

#include <QObject>
#include "igraph.h"
#include "graphlayout.h"
#include "forcedgraphcalculator.h"

class GraphLab : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GraphLayout* graphLayout READ getGraphLayout NOTIFY layoutReady)
public:
    explicit GraphLab(QObject *parent = nullptr);

    // Interface to QML
    Q_INVOKABLE
    void generateGraph(int nodes, int edges);

    Q_INVOKABLE
    void setGraph(const QString &graphDescription);

    Q_INVOKABLE
    GraphLayout *getGraphLayout() const;

    Q_INVOKABLE
    void setAttractiveForce(const QString &force);
    Q_INVOKABLE
    void setRepulsiveForce(const QString &force);

    Q_INVOKABLE
    void setFrameSize(int width, int height);

    Q_INVOKABLE
    void setNodeSize(int width, int height);

    Q_INVOKABLE
    void recalculatePositions();

signals:
    void layoutReady();

private:
    GraphCalculatorConfig config;
    ForcedGraphCalculator::ForcedGraphConfig forces;
    PositionedGraph *graph = nullptr;
    GraphLayout *graphLayout = nullptr;
    ForcedGraphCalculator *calculator = nullptr;
};

#endif // GRAPHLAB_H
