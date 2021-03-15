#ifndef GRAPHCALCULATOR_H
#define GRAPHCALCULATOR_H

#include <QObject>
#include <QRunnable>
#include <QMutex>
#include <QVector>
#include "point.h"
#include "igraph.h"
#include "kmisc/kfunction/kfunction.h"

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
                    QVector<GraphGeometry::Point> &positions,
                    QMutex &lock,
                    GraphCalculatorConfig config);

    Q_INVOKABLE
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
    QVector<GraphGeometry::Point> &positions;
    GraphCalculatorConfig config;
};

#endif // GRAPHCALCULATOR_H
