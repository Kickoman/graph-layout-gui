#include "section.h"
#include "line.h"

namespace GraphGeometry {

bool Section::has(QPointF a) const
{
    Line l(this->start(), this->end());
    double max_x = std::max(_start.x(), _end.x());
    double min_x = std::min(_start.x(), _end.x());
    double max_y = std::max(_start.y(), _end.y());
    double min_y = std::min(_start.y(), _end.y());

    bool res = false;
    if (l.has(a))
    {
        bool x_ok = (min_x < a.x() || qFuzzyCompare(min_x, a.x())) && (max_x > a.x() || qFuzzyCompare(max_x, a.x()));
        bool y_ok = (min_y < a.y() || qFuzzyCompare(min_y, a.y())) && (max_y > a.y() || qFuzzyCompare(max_y, a.y()));
        res = x_ok && y_ok;
    }
    return res;
}

QPointF Section::intersection(const Section &other, bool *ok) const
{
    // Construct two lines
    Line l1(this->start(), this->end());
    Line l2(other.start(), other.end());
    bool found = false;
    QPointF linesIntersectionQPointF = l1.intersection(l2, &found);
    if (found)
        found = this->has(linesIntersectionQPointF) && other.has(linesIntersectionQPointF);
    if (ok) *ok = found;
    return linesIntersectionQPointF;
}
}
