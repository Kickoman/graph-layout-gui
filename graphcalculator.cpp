#include "graphcalculator.h"
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <thread>
#include <QThread>
#include <chrono>

#include "twodvector.h"

GraphCalculator::GraphCalculator(IGraph *graph,
                                 QVector<QPointF> &positions,
                                 QMutex &lock,
                                 GraphCalculatorConfig config)
    : graph(graph)
    , mutex(lock)
    , positions(positions)
    , config(config)
{
}

void GraphCalculator::run()
{
    double temperature = sqrt(config.frameHeight * config.frameHeight
                              + config.frameWidth * config.frameWidth);

    while (temperature > 10)
    {
        QMutexLocker lock(&mutex);

        const int NODES_COUNT = graph->nodesCount();
        QVector<GraphGeometry::TwoDVector> forces(NODES_COUNT, {0, 0});

        // Repulsive forces between each pair of vertices
        for (int targetNode = 0; targetNode < NODES_COUNT; ++targetNode)
        {
            for (int otherNode = 0; otherNode < NODES_COUNT; ++otherNode)
            {
                if (targetNode == otherNode) continue;

                auto myPosition = positions.at(targetNode);
                auto itPosition = positions.at(otherNode);
                // Direction vector should be directed FROM other node,
                // because this is the repulsive force, so it should
                // move target node onto a larger distance from other node.
                auto directionVector = GraphGeometry::TwoDVector(itPosition, myPosition);
                auto distance = directionVector.magnitude();
                auto forceScalar = config.repulsiveForce(distance);
                if (qIsNaN(forceScalar) || qIsInf(forceScalar))
                    forceScalar = static_cast<double>(INT_MAX); // some big value
                auto forceVector = directionVector / distance * forceScalar;
                forces[targetNode] += forceVector;
            }
        }

        // Attractive forces between connected vertices
        const int EDGES_COUNT = graph->edgesCount();
        for (int targetEdge = 0; targetEdge < EDGES_COUNT; ++targetEdge)
        {
            auto currentEdge = graph->edge(targetEdge);
            auto position1 = positions.at(currentEdge.first);
            auto position2 = positions.at(currentEdge.second);

            auto directionVector1 = GraphGeometry::TwoDVector(position1, position2);
            auto directionVector2 = GraphGeometry::TwoDVector(position2, position1);
            auto distance = directionVector1.magnitude();

            assert(qFuzzyCompare(distance, directionVector2.magnitude()));

            auto forceScalar = config.attractiveForce(distance);
            if (qIsNaN(forceScalar) || qIsInf(forceScalar))
                forceScalar = static_cast<double>(INT_MAX);

            auto forceVector1 = directionVector1 / distance * forceScalar;
            auto forceVector2 = directionVector2 / distance * forceScalar;

            forces[currentEdge.first] += forceVector1;
            forces[currentEdge.second] += forceVector2;
        }

        // Compute repulsive forces from frame edges
        auto computeForce
            = [this](double distance, GraphGeometry::TwoDVector direction) -> GraphGeometry::TwoDVector {
            auto forceScalar = config.repulsiveForce(distance) / 7;
            return direction / direction.magnitude() * forceScalar;
        };
        for (int targetNode = 0; targetNode < NODES_COUNT; ++targetNode)
        {
            auto pos = positions.at(targetNode);
            forces[targetNode] += computeForce(pos.y(), {0, 1});                        // from top
            forces[targetNode] += computeForce(config.frameHeight - pos.y(), {0, -1});  // from bottom
            forces[targetNode] += computeForce(pos.x(), {1, 0});                        // from left
            forces[targetNode] += computeForce(config.frameWidth - pos.x(), {-1, 0});
        }

        // Apply forces to nodes
        for (int node = 0; node < NODES_COUNT; ++node)
        {
            double x = positions.at(node).x();
            double y = positions.at(node).y();

            x += std::min(temperature, forces.at(node).x());
            y += std::min(temperature, forces.at(node).y());

            x = std::max(config.nodeWidth / 2, x);
            x = std::min(config.frameWidth - config.nodeWidth / 2, x);
            y = std::max(config.nodeHeight / 2, y);
            y = std::min(config.frameHeight - config.nodeHeight / 2, y);

            positions[node] = QPointF(x, y);
        }

        lock.unlock();
        emit updated();
        temperature /= 1.05;
//        QThread::currentThread()->usleep(50000);
    }
    emit finished();
}
