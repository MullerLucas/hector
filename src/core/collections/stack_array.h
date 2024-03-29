#include <cstddef>
#include <cassert>
#include <cstddef>
#include <iostream>

namespace hell {

template <typename T, std::size_t CAPACITY>
class StackArray {
private:
    T data[CAPACITY];
    std::size_t len;

public:
    std::size_t get_len();
    bool is_empty() const;
    bool is_full() const;
    void push(T value);
    T pop();
    const T& peek() const;
    void print() const;
};



template <typename T, std::size_t CAPACITY>
std::size_t StackArray<T, CAPACITY>::get_len() {
    return this->len;
}

template <typename T, std::size_t CAPACITY>
bool StackArray<T, CAPACITY>::is_empty() const {
    return this->len == 0;
}

template <typename T, std::size_t CAPACITY>
bool StackArray<T, CAPACITY>::is_full() const {
    return this->len == CAPACITY;
}

template <typename T, std::size_t CAPACITY>
void StackArray<T, CAPACITY>::push(T value) {
    assert(!this->is_full());

    this->data[this->len] = value;
    this->len += 1;
}

template <typename T, std::size_t CAPACITY>
T StackArray<T, CAPACITY>::pop() {
    assert(!this->is_empty());

    this->len -= 1;
    return this->data[this->len];
}

template <typename T, std::size_t CAPACITY>
const T& StackArray<T, CAPACITY>::peek() const {
    assert(!this->is_empty());

    return this->data[this->len - 1];
}


template <typename T, std::size_t CAPACITY>
void StackArray<T, CAPACITY>::print() const {
    for (std::size_t i = 0; i < len; i++) {
        std::cout << "Value: " << this->data[i] << std::endl;
    }
}

}
