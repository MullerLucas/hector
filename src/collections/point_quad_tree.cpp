#include "point_quad_tree.hpp"
#include <vector>
#include <cstdint>
#include <cmath>

namespace hell
{

// ----------------------------------------------
// Point2D
// ----------------------------------------------

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

// ----------------------------------------------
// Rect2D
// ----------------------------------------------

Rect2D::Rect2D(float_t x, float_t y, float_t width, float_t height)
    : x(x), y(y), width(width), height(height)
{ }

// -----

std::ostream& operator<<(std::ostream& os, const Rect2D& rect) {
    os << "(" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << ")";
    return os;
}

// -----

bool Rect2D::contains_point(Point2D point)
{
    return point.x >= x && point.x <= x + width &&
           point.y >= y && point.y <= y + height;
}

}
