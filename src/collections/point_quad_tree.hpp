#pragma once

// #include <cmath>
// #include <cstddef>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdint>
#include <cmath>

namespace hell
{

// ----------------------------------------------

struct Point2D
{
    float_t x;
    float_t y;
};

std::ostream& operator<<(std::ostream& os, const Point2D& point);

// ----------------------------------------------

class Rect2D
{
public:
    float_t x;
    float_t y;
    float_t width;
    float_t height;

    Rect2D(float_t x, float_t y, float_t width, float_t height);
    bool contains_point(Point2D point);
};

std::ostream& operator<<(std::ostream& os, const Rect2D& rect);


// ----------------------------------------------

const size_t CHILD_COUNT = 4;
const size_t AREA_COUNT = 4;
const size_t NE_IDX = 0;
const size_t NW_IDX = 1;
const size_t SW_IDX = 2;
const size_t SE_IDX = 3;

template<typename T, size_t CAPACITY>
class PointQuadTreeNode
{
private:
    Rect2D bounds;
    Point2D points[CAPACITY];
    T values[CAPACITY];
    size_t len;
    PointQuadTreeNode<T, CAPACITY>* children[CHILD_COUNT];
    bool is_split;

public:
    PointQuadTreeNode<T, CAPACITY>(Rect2D bounds);

    bool try_insert(Point2D point, T&& value);
    void print() const;

private:
    void split_node();
};

template<typename T, size_t CAPACITY>
PointQuadTreeNode<T, CAPACITY>::PointQuadTreeNode(Rect2D bounds)
   : bounds(bounds), len(0), is_split(false)
{ }

template<typename T, size_t CAPACITY>
bool PointQuadTreeNode<T, CAPACITY>::try_insert(Point2D point, T&& value)
{
    if (!this->bounds.contains_point(point))
        return false;

    if (!this->is_split)
    {
        if (this->len < CAPACITY)
        {
            this->points[this->len] = point;
            this->values[this->len] = value;
            this->len += 1;
            return true;
        }

        this->split_node();
    }

    for (size_t i = 0; i < AREA_COUNT; i++)
    {
        if (this->children[i]->try_insert(point, std::move(value)))
            return true;
    }

    return false;
}

template<typename T, size_t CAPACITY>
void PointQuadTreeNode<T, CAPACITY>::print() const
{
    std::cout << "----------" << std::endl;

    std::cout << "Bounds: " << this->bounds << std::endl;
    std::cout << "Len: "    << this->len << std::endl;
    std::cout << "Data: "   << std::endl;
    for (size_t i = 0; i < this->len; i++)
    {
        std::cout << i << " => [" << this->points[i] << "; " << this->values[i] << "] ";
    }
    std::cout << std::endl;

    std::cout << "Children: " << std::endl;
    if (this->is_split)
    {
        for (size_t i = 0; i < AREA_COUNT; i++)
        {
            this->children[i]->print();
        }
    } else {
        std::cout << "none" << std::endl;
    }

    std::cout << "----------" << std::endl;
}

// -----

template<typename T, size_t CAPACITY>
void PointQuadTreeNode<T, CAPACITY>::split_node()
{
    this->children[NE_IDX] = new PointQuadTreeNode<T, CAPACITY> { {
        this->bounds.x,
        this->bounds.y,
        this->bounds.x + this->bounds.width  / 2.0f,
        this->bounds.y + this->bounds.height / 2.0f
    } };

    this->children[NW_IDX] = new PointQuadTreeNode<T, CAPACITY> { {
        this->bounds.x + this->bounds.width  / 2.0f,
        this->bounds.y,
        this->bounds.x + this->bounds.width,
        this->bounds.y + this->bounds.height / 2.0f,
    } };

    this->children[SW_IDX] = new PointQuadTreeNode<T, CAPACITY> { {
        this->bounds.x + this->bounds.width  / 2.0f,
        this->bounds.y + this->bounds.height / 2.0f,
        this->bounds.x + this->bounds.width,
        this->bounds.y + this->bounds.height,
    } };

    this->children[SW_IDX] = new PointQuadTreeNode<T, CAPACITY> { {
        this->bounds.x,
        this->bounds.y + this->bounds.height / 2.0f,
        this->bounds.x + this->bounds.width  / 2.0f,
        this->bounds.y + this->bounds.height,
    } };


    this->is_split = true;
}

// ----------------------------------------------

template<typename T, size_t CAPACITY>
class PointQuadTree
{
private:
    PointQuadTreeNode<T, CAPACITY>* root;

public:
    PointQuadTree(Rect2D bounds);
    PointQuadTree(const PointQuadTreeNode<T, CAPACITY>& other);
    PointQuadTree(PointQuadTreeNode<T, CAPACITY>&& other);
    ~PointQuadTree();

    PointQuadTree<T, CAPACITY>& operator=(const PointQuadTree<T, CAPACITY>& other);
    PointQuadTree<T, CAPACITY>& operator=(PointQuadTree<T, CAPACITY>&& other);

    bool try_insert(Point2D point, T&& value);
    void query(std::vector<T>& collector);
    void print() const;
};

// ---

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>::PointQuadTree(Rect2D bounds)
{
    root = new PointQuadTreeNode<T, CAPACITY>(bounds);
}

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>::PointQuadTree(const PointQuadTreeNode<T, CAPACITY>& other)
{
    // TODO(lm): implement
}

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>::PointQuadTree(PointQuadTreeNode<T, CAPACITY>&& other)
{
    // TODO(lm): implement
}

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>::~PointQuadTree()
{
    // TODO(lm): implement
}

// -----

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>& PointQuadTree<T, CAPACITY>::operator=(const PointQuadTree<T, CAPACITY>& other)
{
    // TODO(lm): implement
}

template<typename T, size_t CAPACITY>
PointQuadTree<T, CAPACITY>& PointQuadTree<T, CAPACITY>::operator=(PointQuadTree<T, CAPACITY>&& other)
{
    // TODO(lm): implement
}


// -----

template<typename T, size_t CAPACITY>
bool PointQuadTree<T, CAPACITY>::try_insert(Point2D point, T&& value)
{
    return this->root->try_insert(point, std::move(value));
}

template<typename T, size_t CAPACITY>
void PointQuadTree<T, CAPACITY>::print() const
{
    this->root->print();
}

}
