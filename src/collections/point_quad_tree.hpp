#pragma once

#include <cmath>
#include <cstddef>
#include <vector>
#include "point_2d.h"
#include "rect_2d.h"

namespace hell
{

// ----------------------------------------------

const std::size_t CHILD_COUNT = 4;

template<typename T, std::size_t CAPACITY>
class PointQuadTreeNode
{
private:
    Rect2D bounds;
    T values[CAPACITY];
    PointQuadTreeNode<T, CAPACITY>* children[CHILD_COUNT];
    bool is_divides;

public:
    PointQuadTreeNode<T, CAPACITY>(Rect2D bounds);

};

template<typename T, std::size_t CAPACITY>
PointQuadTreeNode<T, CAPACITY>::PointQuadTreeNode(Rect2D bounds)
   : bounds(bounds), is_divides(false)
{ }

// ----------------------------------------------

template<typename T, std::size_t CAPACITY>
class PointQuadTree
{
private:
    PointQuadTreeNode<T, CAPACITY>* root;

public:
    PointQuadTree(Rect2D bounds);

    void insert(Point2D point);
    void query(std::vector<T>& collector);
};

template<typename T, std::size_t CAPACITY>
PointQuadTree<T, CAPACITY>::PointQuadTree(Rect2D bounds)
{
    root = new PointQuadTreeNode<T, CAPACITY>(bounds);
}

}
