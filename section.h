#ifndef SECTION_H
#define SECTION_H

#include <QPointF>

namespace GraphGeometry {

class Section
{
public:
    Section() = default;
    Section(QPointF a, QPointF b) : _start(a), _end(b) {}
    Section(double x1, double y1, double x2, double y2) : _start(x1, y1), _end(x2, y2) {}

    QPointF start() const { return _start; }
    QPointF end() const { return _end; }

    bool has(QPointF a) const;

    QPointF intersection(const Section &other, bool *ok = nullptr) const;
private:
    QPointF _start{};
    QPointF _end{};
};
}

#endif // SECTION_H
