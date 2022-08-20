// list psl header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef PSL_LIST_H_
#define PSL_LIST_H_
#include <psl_yvals_core.h>

#include <cstddef>
#include <memory>

PSL_BEGIN

template <class ForwardIterator, class OutputIterator>
OutputIterator copy(ForwardIterator first, ForwardIterator last, OutputIterator result) {
    for (; first != last; ++first, ++result) {
        *result = *first;
    }

    return result;
}

template <class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first) {
        first->~Ty();
    }
}

template <class Tp, class Alloc = std::allocator<Tp>>
class List {
private:
    using Alty_traits = typename Alloc::template rebind<Tp>::other;

public:
    using value_type = Tp;
    using allocator_type = Alloc;
    using pointer = typename Alty_traits::pointer;
    using const_pointer = typename Alty_traits::const_pointer;
    using reference = Tp&;
    using const_reference = const Tp&;
    using size_type = std::size_t;
    using difference_type = typename Alty_traits::difference_type;

    List(size_type n = size_type(), const_reference value = value_type(), const allocator_type alloc = allocator_type())
        : alloc{alloc} {
        elements = allocator_type::allocate(n);

        try {
            std::uninitialized_fill_n(elements, elements + n, value);
            space = last = elements + n;
        } catch (...) {
            allocator_type::deallocate(elements, n);
            throw;
        }
    }

    List(const List& other) = delete;

    List(List&& other) : alloc{other.alloc}, elements{other.elements}, space{other.space}, last{other.last} {
        other.elements = other.space = other.last = nullptr;
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        List tmp{other};
        swap(*this, tmp);
        return *this;
    }

    pointer begin() noexcept {
        return elements;
    }

    const_pointer begin() const noexcept {
        return elements;
    }

    pointer end() noexcept {
        return space;
    }

    const_pointer end() const noexcept {
        return space;
    }

    reference front() noexcept {
        return *begin();
    }

    const_reference front() const noexcept {
        return *begin();
    }

    reference back() noexcept {
        return *(end() - 1);
    }

    const_reference back() const noexcept {
        return *(end() - 1);
    }

    size_type size() const noexcept {
        return last - elements;
    }

    size_type capacity() const noexcept {
        return space - elements;
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    void reserve(size_type newalloc) {
        if (newalloc <= capacity()) {
            return;
        }

        List<value_type, allocator_type> tmp{newalloc, alloc};
    }

    ~List() {
        delete[] elements;
    }

    reference operator[](const size_type& i) noexcept {
        return elements[i];
    }

    const_reference operator[](const size_type& i) const noexcept {
        return elements[i];
    }

private:
    pointer elements;
    pointer space;
    pointer last;
    allocator_type alloc;
};

PSL_END

#endif  // PSL_LIST_H_