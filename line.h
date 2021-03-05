#ifndef LINE_H
#define LINE_H

#include <QPointF>
#include "twodvector.h"

namespace GraphGeometry {

class Line
{
public:
    Line();
    /// \brief cieraz paspalitaje
    Line(double a, double b, double c);
    /// \brief cieraz kutny
    Line(double k, double b);
    /// \brief cieraz punkty
    Line(QPointF a, QPointF b);
    Line(QPointF a, TwoDVector directionVector);

    // Paspalitaje
    double A() const;
    double B() const;
    double C() const;

    // Kutny kaef
    double k() const;
    double b() const;

    bool has(QPointF p) const;

    QPointF intersection(const Line &other, bool *ok = nullptr) const;

private:
    double _a = 0;
    double _b = 1;
    double _c = 0;
};

}

#endif // LINE_H
