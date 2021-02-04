#ifndef GRAPHCALCULATOR_H
#define GRAPHCALCULATOR_H

#include <QObject>
#include <QRunnable>
#include <QMutex>
#include <QVector>
#include <QPointF>
#include "igraph.h"
#include "kfunction.h"

struct GraphCalculatorConfig
{
    Function<double> repulsiveForce;
    Function<double> attractiveForce;

    double nodeWidth = 100;
    double nodeHeight = 100;
};


class GraphCalculator : public QObject, public QRunnable
{
    Q_OBJECT
public:
    GraphCalculator(IGraph *graph,
                    QVector<QPointF> &positions,
                    QMutex &lock,
                    GraphCalculatorConfig config);

    void run() override;

signals:
    void finished();

private:
    IGraph *graph;
    QMutex &mutex;
    QVector<QPointF> &positions;
    GraphCalculatorConfig config;
};

#endif // GRAPHCALCULATOR_H
