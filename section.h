#ifndef SECTION_H
#define SECTION_H

#include <QPointF>

namespace GraphGeometry {

class Section
{
public:
    /// \brief Constructs zero-length section
    Section() = default;
    ///
    /// \brief Constructs section by two points
    /// \param a Section start point
    /// \param b Section finish point
    ///
    Section(QPointF a, QPointF b) : _start(a), _end(b) {}
    ///
    /// \brief Constructs section by two points' coordinates
    /// \param x1 Section start point x coordinate
    /// \param y1 Section start point y coordinate
    /// \param x2 Section finish point x coordinate
    /// \param y2 Section finish point y coordinate
    ///
    Section(double x1, double y1, double x2, double y2) : _start(x1, y1), _end(x2, y2) {}

    ///
    /// \brief Getter for section start point
    /// \return Section start point
    ///
    QPointF start() const { return _start; }
    ///
    /// \brief Getter for section finish point
    /// \return Section finish point
    ///
    QPointF end() const { return _end; }

    ///
    /// \brief Checks if the point belongs to the section
    /// \param a The point to be checked
    /// \return true if the point belongs to the section, false otherwise
    ///
    bool has(QPointF a) const;

    ///
    /// \brief Finds the intersection point of two sectinos
    /// \param other Another section to find the intersection point with
    /// \param ok Optional output parameter which will be set as true if the intersection point was found.
    ///        false otherwise
    /// \return The intersection point
    ///
    QPointF intersection(const Section &other, bool *ok = nullptr) const;
private:
    QPointF _start{};
    QPointF _end{};
};
}

#endif // SECTION_H
