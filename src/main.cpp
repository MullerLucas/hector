#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <utility>

#include "collections/bs_tree.hpp"
#include "collections/linked_list.hpp"
#include "collections/point_quad_tree.hpp"
#include "collections/stack_array.hpp"



void test_stack_array()
{
    std::cout << "test stack array" << std::endl;

    auto stack = hell::StackArray<std::int32_t, 5> {};

    std::cout << "Is empty: " << stack.is_empty() << std::endl;
    std::cout << "Is full: "  << stack.is_full()  << std::endl;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    stack.push(5);
    assert(stack.is_empty() == false);
    assert(stack.is_full()  == true);

    assert(stack.pop() == 5);
    assert(stack.is_full() == false);
    assert(stack.peek() == 4);

    stack.print();

    const auto stack_2 = hell::StackArray<int32_t, 5>(stack);
    stack_2.print();
}

void test_linked_list()
{
    std::cout << "test linked list" << std::endl;

    auto list = hell::LinkedList<int> {};

    list.push_head(1);
    assert(list.get_len()   == 1);
    assert(list.peek_head() == 1);
    assert(list.peek_tail() == 1);

    list.push_head(2);
    assert(list.get_len()   == 2);
    assert(list.peek_head() == 2);
    assert(list.peek_tail() == 1);

    list.push_tail(3);
    assert(list.get_len()   == 3);
    assert(list.peek_head() == 2);
    assert(list.peek_tail() == 3);

    assert(list.pop_head() == 2);
    assert(list.pop_tail() == 3);

    list.insert_at(0, 11);
    assert(list.peek_head() == 11);

    list.insert_at(2, 12);
    assert(list.peek_tail() == 12);

    list.insert_at(1, 13);
    assert(list.peek_at(1) == 13);

    assert(list.remove_at(2) == 1);
    assert(list.remove_at(0) == 11);
    assert(list.remove_at(1) == 12);

    std::cout << "copy:" << std::endl;
    auto list_2 = list;
    list.print();
    list_2.print();

    std::cout << "move:" << std::endl;
    auto list_3 = std::move(list);
    list.print();
    list_3.print();
}

void test_bs_tree()
{
    auto print_func = [](int value) { std::cout << "[" << value << "]" << std::endl; };

    auto tree = hell::BSTree<int> {};
    tree.insert(100);

    tree.insert(50);
    tree.insert(25);
    tree.insert(20);
    tree.insert(30);
    tree.insert(75);
    tree.insert(70);
    tree.insert(80);
    tree.insert(150);
    tree.insert(150);
    tree.insert(175);
    tree.insert(125);

    auto tree_clone = hell::BSTree<int> { tree };

    std::cout << "----- insert -----" << std::endl;
    tree.traverse_pre_order(print_func);

    tree.remove(50);
    std::cout << "----- remove -----" << std::endl;
    tree.traverse_pre_order(print_func);

    tree.rotate_right();
    std::cout << "----- rotate right -----" << std::endl;
    tree.traverse_pre_order(print_func);

    tree.rotate_left();
    std::cout << "----- rotate left  -----" << std::endl;
    tree.traverse_pre_order(print_func);

    std::cout << "-----  clone -----" << std::endl;
    tree_clone.traverse_pre_order(print_func);

    // std::cout << "-----   pre -----" << std::endl;
    // tree.traverse_pre_order(func);
    // std::cout << "-----    in -----" << std::endl;
    // tree.traverse_in_order(func);
    // std::cout << "-----  post -----" << std::endl;
    // tree.traverse_post_order(func);
    // std::cout << "----- level -----" << std::endl;
    // tree.traverse_level_order(func);
}

void test_point_quad_tree()
{
    const auto bounds = hell::Rect2D { 0, 0, 100, 100 };
    auto tree = hell::PointQuadTree<size_t, 4> { bounds };

    tree.try_insert({ 10, 10}, 0);
    tree.try_insert({ 20, 20}, 1);
    tree.try_insert({ 30, 30}, 2);
    tree.try_insert({ 40, 40}, 3);
    // tree.try_insert({ 50, 50}, 4);
    tree.print();

}

int main(int argc, char *argv[])
{
    std::cout << "hell(o) world" << std::endl;
    // test_stack_array();
    // test_linked_list();
    // test_bs_tree();
    test_point_quad_tree();
}
