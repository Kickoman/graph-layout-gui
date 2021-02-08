#include "graphcalculator.h"
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>

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

            auto force_scalar = dist * dist / 10;

            if (qIsNaN(force_scalar))
            {
                qDebug() << "force is nan";
            }

            auto force_vector = Vector{force_scalar, 0};
            auto angle = getAngle(force_vector, dir_vector);
            force_vector = rotate(force_vector, angle);

            forces[target_node] = add(forces[target_node], force_vector);
        }
    }

    const auto edges = graph->edgesCount();
    for (int target_edge = 0; target_edge < edges; ++target_edge)
    {
        auto edge = graph->edge(target_edge);

        auto pos1 = positions.at(edge.first);
        auto pos2 = positions.at(edge.second);

        auto dist = distance(pos1, pos2);
        auto dir1 = vec_from_point(pos1, pos2);
        auto dir2 = vec_from_point(pos2, pos1);

        //        auto force_scalar = config.attractiveForce(dist);
        auto force_scalar = dist > 0 ? -1000/dist : 10000;
        if (qIsNaN(force_scalar))
        {
            qDebug() << "force is nan";
        }

        auto force_vector = Vector{force_scalar, 0};
        auto angle1 = getAngle(force_vector, dir1);
        auto angle2 = getAngle(force_vector, dir2);

        auto force_vector_1 = rotate(force_vector, angle1);
        auto force_vector_2 = rotate(force_vector, angle2);

        forces[edge.first] = add(forces[edge.first], force_vector_1);
        forces[edge.second] = add(forces[edge.second], force_vector_2);
    }

    for (int node = 0; node < N; ++node)
    {
        double new_x = positions[node].x();
        double new_y = positions[node].y();

        new_x += forces[node][0];
        new_y += forces[node][1];

        new_x = std::max(config.nodeWidth / 2, new_x);
        new_x = std::min(config.frameWidth - config.nodeWidth / 2, new_x);
        new_y = std::max(config.nodeHeight / 2, new_y);
        new_y = std::min(config.frameHeight - config.nodeHeight / 2, new_y);

        positions[node] = QPointF(new_x, new_y);
    }

    //    for (int target_node = 0; target_node < N; ++target_node)
    //    {
    //        Vector force = {0, 0};
    //        for (int other_node = 0; other_node < N; ++other_node)
    //        {
    //            if (target_node == other_node) continue;

    //            auto my_position = positions.at(target_node);
    //            auto it_position = positions.at(other_node);
    //            auto dist = distance(my_position, it_position);

    //            Vector direction_vector = {0, 0};
    //            double force_scalar = 0;

    //            if (graph->isAdjacent(target_node, other_node))
    //            {
    //                direction_vector = vec_from_point(my_position,
    //                                                  it_position);
    //                force_scalar = config.attractiveForce(dist);
    //            }
    //            else
    //            {
    //                direction_vector = vec_from_point(it_position,
    //                                                  my_position);
    //                force_scalar = config.repulsiveForce(dist);
    //            }

    //            Vector current_force{force_scalar, 0};
    //            auto angle = getAngle(current_force, direction_vector);
    //            current_force = rotate(current_force, angle);
    //            force = add(force, current_force);
    //        }

    //        positions[target_node] = QPointF(positions[target_node].x() + force[0],
    //                                         positions[target_node].y() + force[1]);
    //    }
    emit finished();

    qDebug() << "positions:";
    for (int i = 0; i < N; ++i)
        qDebug().noquote() << QString("{%1, %2} -- {%3, %4}")
                                  .arg(positions[i].x())
                                  .arg(positions[i].y())
                                  .arg(forces[i][0])
                                  .arg(forces[i][1]);
}
