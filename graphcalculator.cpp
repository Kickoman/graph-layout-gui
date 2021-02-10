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

void GraphCalculator::run2()
{
    // TODO: refactor
    using Vector = std::array<double, 2>;
    auto rad_to_deg = [](double rad){ return (rad * 180) / M_PI; };
    auto deg_to_rad = [](double deg){ return (deg * M_PI) / 180; };
    auto add        = [](const Vector a, const Vector b) -> Vector {
        Vector res;
        res[0] = a[0] + b[0];
        res[1] = a[1] + b[1];
        return res;
    };
    auto multiply   = [](const Vector a, double number) -> Vector {
        Vector res;
        res[0] = a[0] * number;
        res[1] = a[1] * number;
        return res;
    };
    auto divide     = [](const Vector a, double number) -> Vector {
        Vector res;
        res[0] = a[0] / number;
        res[1] = a[1] / number;
        return res;
    };
    auto dot        = [](const Vector a, const Vector b) -> double {
        return a[0]*b[0] + a[1]*b[1];
    };
    auto magnitude  = [](const Vector a) -> double {
        return sqrt(a[0]*a[0]+a[1]*a[1]);
    };
    auto rotate     = [](const Vector a, double radians) -> Vector {
        Vector res;
        res[0] = cos(radians) * a[0] - sin(radians) * a[1];
        res[1] = sin(radians) * a[0] + cos(radians) * a[1];
        return res;
    };
    auto getAngle   = [&](const Vector a, const Vector b) -> double {
        double product = dot(a, b);
        double a_magn  = magnitude(a);
        double b_magn  = magnitude(b);
        double angle_cos = product / (a_magn * b_magn);
        return acos(angle_cos);
    };
    auto getAngleOrRandom = [&](const Vector a, const Vector b) -> double {
        auto angle = getAngle(a, b);
        return qIsNaN(angle) ? deg_to_rad(rand() % 360) : angle;
    };
    auto distance   = [](QPointF a, QPointF b) -> double {
        qreal _x2 = (a.x() - b.x()) * (a.x() - b.x());
        qreal _y2 = (a.y() - b.y()) * (a.y() - b.y());
        return sqrt(_x2 + _y2);
    };
    auto vec_from_point = [](QPointF from, QPointF to) -> Vector {
        Vector res;
        res[0] = to.x() - from.x();
        res[1] = to.y() - from.y();
        return res;
    };

    double temperature = sqrt(config.frameHeight * config.frameHeight + config.frameWidth * config.frameWidth);

    while (temperature > 10)
    {
        QMutexLocker lock(&mutex);
        const int N = graph->nodesCount();
        std::vector<Vector> forces(N, Vector{0, 0});
        for (int target_node = 0; target_node < N; ++target_node)
        {
            for (int other_node = 0; other_node < N; ++other_node)
            {
                if (target_node == other_node) continue;

                auto my_pos = positions.at(target_node);
                auto it_pos = positions.at(other_node);
                auto dist = distance(my_pos, it_pos);
                auto dir_vector = vec_from_point(it_pos, my_pos);
                auto unit_vector = divide(dir_vector, magnitude(dir_vector));
                auto force_scalar = config.repulsiveForce(dist);
                if (qIsNaN(force_scalar))
                {
                    qDebug() << "force is nan";
                    force_scalar = INT_MAX;
                }
                auto force_vector = multiply(unit_vector, force_scalar);
                forces[target_node] = add(forces[target_node], force_vector);
            }
        }

        qDebug() << "Temperature: " << temperature;
        qDebug() << "Forces & positions 1:";
        for (int i = 0; i < N; ++i)
            qDebug().noquote() << QString("{%1, %2} -- {%3, %4}")
                                      .arg(positions[i].x())
                                      .arg(positions[i].y())
                                      .arg(forces[i][0])
                                      .arg(forces[i][1]);

        const auto edges = graph->edgesCount();
        for (int target_edge = 0; target_edge < edges; ++target_edge)
        {
            auto edge = graph->edge(target_edge);

            auto pos1 = positions.at(edge.first);
            auto pos2 = positions.at(edge.second);

            auto dist = distance(pos1, pos2);
            auto dir1 = vec_from_point(pos1, pos2);
            auto dir2 = vec_from_point(pos2, pos1);

            auto unit1 = divide(dir1, magnitude(dir1));
            auto unit2 = divide(dir2, magnitude(dir2));

            auto force_scalar = config.attractiveForce(dist);
            if (qIsNaN(force_scalar))
            {
                qDebug() << "force is nan";
                force_scalar = INT_MAX;
            }

            auto force_vector = Vector{force_scalar, 0};

            auto force_vector_1 = multiply(unit1, force_scalar);
            auto force_vector_2 = multiply(unit2, force_scalar);

            forces[edge.first] = add(forces[edge.first], force_vector_1);
            forces[edge.second] = add(forces[edge.second], force_vector_2);
        }

        qDebug() << "Forces & positions 2:";
        for (int i = 0; i < N; ++i)
            qDebug().noquote() << QString("{%1, %2} -- {%3, %4}")
                                      .arg(positions[i].x())
                                      .arg(positions[i].y())
                                      .arg(forces[i][0])
                                      .arg(forces[i][1]);

        // Compute repulsive forces from frame edges
        for (int target_node = 0; target_node < N; ++target_node)
        {
            // from top
            auto dist = positions.at(target_node).y();
            auto dir_vector = Vector{0, 1};
            auto force_scalar = config.repulsiveForce(dist) / 2;
            auto force_vector = multiply(dir_vector, force_scalar);
            forces[target_node] = add(forces[target_node], force_vector);

            // from bottom
            dist = config.frameHeight - positions.at(target_node).y();
            dir_vector = Vector{0, -1};
            force_scalar = config.repulsiveForce(dist) / 2;
            force_vector = multiply(dir_vector, force_scalar);
            forces[target_node] = add(forces[target_node], force_vector);

            // from left
            dist = positions.at(target_node).x();
            dir_vector = Vector{1, 0};
            force_scalar = config.repulsiveForce(dist) / 2;
            force_vector = multiply(dir_vector, force_scalar);
            forces[target_node] = add(forces[target_node], force_vector);

            // from right
            dist = config.frameWidth - positions.at(target_node).x();
            dir_vector = Vector{-1, 0};
            force_scalar = config.repulsiveForce(dist) / 2;
            force_vector = multiply(dir_vector, force_scalar);
            forces[target_node] = add(forces[target_node], force_vector);
        }

        for (int node = 0; node < N; ++node)
        {
            double new_x = positions[node].x();
            double new_y = positions[node].y();

            new_x += std::min(temperature, forces[node][0]);
            new_y += std::min(temperature, forces[node][1]);

            new_x = std::max(config.nodeWidth / 2, new_x);
            new_x = std::min(config.frameWidth - config.nodeWidth / 2, new_x);
            new_y = std::max(config.nodeHeight / 2, new_y);
            new_y = std::min(config.frameHeight - config.nodeHeight / 2, new_y);

            positions[node] = QPointF(new_x, new_y);
        }


        lock.unlock();
        emit updated();
        temperature /= 1.05;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    emit finished();

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
