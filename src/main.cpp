#include <cstdint>
#include <iostream>
#include <ostream>
#include <utility>

#include "collections/stack_array.hpp"



void test_stack_array()
{
    auto stack = hell::StackArray<std::int32_t, 5> {};

    std::cout << "Is empty: " << stack.is_empty() << std::endl;
    std::cout << "Is full: "  << stack.is_full()  << std::endl;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    std::cout << "Is empty: " << stack.is_empty() << std::endl;
    std::cout << "Is full: "  << stack.is_full()  << std::endl;
    std::cout << "Popping: "  << stack.pop()      << std::endl;
    std::cout << "Peeking: "  << stack.peek()     << std::endl;

    stack.print();

    const auto stack_2 = hell::StackArray<std::int32_t, 5>(stack);
    const auto stack_3 = hell::StackArray<std::int32_t, 5>(std::move(stack));
}

int main(int argc, char *argv[]) {
    std::cout << "hell(o) world" << std::endl;
    test_stack_array();
}
