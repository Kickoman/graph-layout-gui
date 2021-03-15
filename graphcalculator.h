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

    double frameWidth = 1000;
    double frameHeight = 1000;
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
    void updated();
    void finished();

private:
    static const double kMinimalTemperature;
    static const double kTemperatureDecreasingFactor;
    static const int kDelayUs;
    static const int kMaxDegrees;
    static const int kRightAngleDeg;
    static const int kEdgesRepulsiveDecreasingFactor;
    static const int kLinesRepulsiveDecreasingFactor;

    IGraph *graph;
    QMutex &mutex;
    QVector<QPointF> &positions;
    GraphCalculatorConfig config;
};

#endif // GRAPHCALCULATOR_H
