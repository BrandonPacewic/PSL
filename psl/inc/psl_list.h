// list psl header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef PSL_LIST_H_
#define PSL_LIST_H_
#include <psl_yvals_core.h>

#include <cstdint>
#include <vector>

PSL_BEGIN

template <class Tp>
class list : public std::vector<Tp> {
public:
    using std::vector<Tp>::vector;
    using value_type = typename std::vector<Tp>::value_type;
    using size_type = typename std::vector<Tp>::size_type;
    using reference = typename std::vector<Tp>::reference;
    using const_reference = typename std::vector<Tp>::const_reference;
    using iterator = typename std::vector<Tp>::iterator;
    using const_iterator = typename std::vector<Tp>::const_iterator;

    list& operator+=(const value_type& val) { // push_back by += operator
        this->push_back(val);
        return *this;
    }

    [[nodiscard]] reference operator[](const size_type& i) {
        constexpr uint8_t invert_list_cutoff = 0;

        // Python inverse list access through negative indices.
        if (i < invert_list_cutoff) {
            return this->at(this->size() - i - 1);
        }

        return this->at(i);
    }

    [[nodiscard]] const_reference operator[](const size_type& i) const {
        constexpr uint8_t invert_list_cutoff = 0;

        // Python inverse list access through negative indices.
        if (i < invert_list_cutoff) {
            return this->at(this->size() - i - 1);
        }

        return this->at(i);
    }

    [[nodiscard]] size_type len() const { // len in addition to std::vector::size()
        return this->size();
    }


    void insert(const size_type& i, const value_type& val) { // insert by index rather than by iterator
        this->insert(this->begin() + i, val);
    }
};

PSL_END

#endif  // PSL_LIST_H_
