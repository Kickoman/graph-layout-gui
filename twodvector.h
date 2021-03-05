#ifndef TWODVECTOR_H
#define TWODVECTOR_H

#include <QPointF>
#define _USE_MATH_DEFINES
#include <math.h>

namespace GraphGeometry {

inline double rad_to_deg(double rad) { return (rad * 180) / M_PI; }
inline double deg_to_rad(double deg) { return (deg * M_PI) / 180; }

class TwoDVector
{
public:
    TwoDVector();
    TwoDVector(double x, double y);
    TwoDVector(QPointF from, QPointF to);
    double x() const;
    double y() const;
    TwoDVector &operator+=(GraphGeometry::TwoDVector other);
    TwoDVector operator+(GraphGeometry::TwoDVector other) const;
    double dotProduct(GraphGeometry::TwoDVector other) const;
    double magnitude() const;
    TwoDVector rotateDeg(double degrees) const;
    TwoDVector rotateRad(double radians) const;
    TwoDVector multiply(double number) const;
    TwoDVector divide(double number) const;
private:
    double _x = 0;
    double _y = 0;
};

TwoDVector operator*(GraphGeometry::TwoDVector v, double number);
TwoDVector operator/(GraphGeometry::TwoDVector v, double number);

}
#endif // TWODVECTOR_H
