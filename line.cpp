#include "line.h"
#include "twodvector.h"

#include <cmath>
#include <cstdlib>

namespace GraphGeometry {

Line::Line() = default;
Line::Line(double a, double b, double c)
    : _a(a), _b(b), _c(c) {}
Line::Line(double k, double b)
{
    _a = k;
    _b = -1;
    _c = b;
    if (_a < 0)
    {
        _a *= -1;
        _b *= -1;
        _c *= -1;
    }
}
Line::Line(QPointF a, QPointF b)
{
    _a = b.y() - a.y();
    _b = a.x() - b.x();
    _c = b.x()*a.y()-a.x()*b.y();

    if (!qFuzzyCompare(_b, 0))
    {
        _a /= qAbs(_b);
        _c /= qAbs(_b);
        _b /= qAbs(_b);
    }
}

Line::Line(QPointF a, TwoDVector directionVector)
{
    _a = directionVector.y();
    _b = -directionVector.x();
    _c = directionVector.x() * a.y() - a.x() * directionVector.y();
    if (!qFuzzyCompare(_b, 0))
    {
        _a /= qAbs(_b);
        _c /= qAbs(_b);
        _b /= qAbs(_b);
    }
}

double Line::A() const { return _a; }
double Line::B() const { return _b; }
double Line::C() const { return _c; }

double Line::k() const { return _b < 0 ? _a : -_a; }
double Line::b() const { return _b < 0 ? _c : -_c; }

bool Line::has(QPointF p) const { return qFuzzyCompare(_a * p.x() + _b * p.y() + _c, 0); }

QPointF Line::intersection(const Line &other, bool *ok) const
{
    double x = 0, y = 0;
    double det = this->A() * other.B() - other.A() * this->B();
    if (ok) *ok = (!qFuzzyCompare(_b, 0));
    if (!qFuzzyCompare(_b, 0))
    {
        x = - (other.B()*this->C() - this->B()*other.C()) / det;
        y = - (this->A()*other.C() - other.A()*this->C()) / det;
    }
    return {x, y};
}


}
