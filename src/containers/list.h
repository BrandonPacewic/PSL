/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#ifndef PYTHON_CPP_LIST_H_
#define PYTHON_CPP_LIST_H_

#include <cstddef>

namespace python_style_cpp {
namespace internal {

template <class ForwardIterator, class Ty>
void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                        const Ty& value) {
    for (; first != last; ++first) {
        ::new (static_cast<void*>(&*first)) Ty(value);
    }
}

template <class ForwardIterator, class OutputIterator>
OutputIterator copy(ForwardIterator first, ForwardIterator last,
                    OutputIterator result) {
    for (; first != last; ++first, ++result) {
        *result = *first;
    }

    return result;
}

template <class Ty>
void swap(Ty& a, Ty& b) {
    Ty tmp = a;
    a = b;
    b = tmp;
}

template <class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first) {
        first->~Ty();
    }
}

}  // namespace internal

template <class Tp>
class List {
   public:
    using value_type = Tp;
    using pointer = Tp*;
    using reference = Tp&;
    using const_pointer = const Tp*;
    using const_reference = const Tp&;
    using iterator = Tp*;
    using const_iterator = const Tp*;
    using size_type = std::size_t;

    List() : elements{nullptr}, space{nullptr}, last{nullptr} {}

    List(size_type n, const Tp& value = value_type())
        : elements{new Tp[n]}, space{elements + n}, last{elements} {
        internal::uninitialized_fill(elements, space, value);
    }

    List(const List& other)
        : elements{new Tp[other.size()]},
          space{elements + other.size()},
          last{elements} {
        internal::uninitialized_fill(elements, space, other.elements);
    }

    List(List&& other)
        : elements{other.elements}, space{other.space}, last{other.last} {
        other.elements = nullptr;
        other.space = nullptr;
        other.last = nullptr;
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        List<value_type> tmp(other);
        internal::uninitialized_fill(elements, space, tmp.elements);
        internal::destroy(tmp.elements, tmp.space);
        

        return *this;
    }

    pointer begin() noexcept { return elements; }

    const_pointer begin() const noexcept { return elements; }

    pointer end() noexcept { return space; }

    const_pointer end() const noexcept { return space; }

    reference front() noexcept { return *begin(); }

    const_reference front() const noexcept { return *begin(); }

    reference back() noexcept { return *(end() - 1); }

    const_reference back() const noexcept { return *(end() - 1); }

    size_type size() const noexcept { return last - elements; }

    size_type capacity() const noexcept { return space - elements; }

    void reserve(size_type newalloc) {
        if (newalloc <= capacity()) {
            return;
        }

        List<value_type> temporary(newalloc);
        internal::copy(begin(), end(), temporary.begin());
        internal::swap(*this, temporary);
    }

    void resize(size_type newsize, const value_type& value = value_type()) {
        reserve(newsize);

        if (size() < newsize) {
            internal::uninitialized_fill(end(), begin() + newsize, value);
        } else {
            internal::destroy(begin() + newsize, end());
        }

        last = begin() + newsize;
    }

    void push_back(const value_type& value) {
        if (space == last) {
            reserve((size()) ? 1.5 * size() : 2);
        }

        *last = value;
        ++last;
    }                

    ~List() { delete[] elements; }

    reference operator[](const size_type& i) noexcept { return elements[i]; }

    const_reference operator[](const size_type& i) const noexcept {
        return elements[i];
    }

   private:
    pointer elements;
    pointer space;
    pointer last;
};

}  // namespace python_style_cpp

#endif  // PYTHON_CPP_LIST_H_