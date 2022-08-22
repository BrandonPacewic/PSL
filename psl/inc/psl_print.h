// print psl header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef PSL_PRINT_H_
#define PSL_PRINT_H_
#include <psl_yvals_core.h>

#include <iostream>
#include <string>

PSL_BEGIN

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value,
                                                                     typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '[';
    std::string separator;

    for (const T& item : container) {
        os << separator << item, separator = ", ";
    }

    return os << ']';
}

void handle_print() {
    std::cout << std::endl;
}

template <class Head, class... Tail>
void handle_print(Head head, Tail... tail) {
    std::cout << head << " ";
    handle_print(tail...);
}

#define print(...) handle_print(__VA_ARGS__)

PSL_END

#endif  // PSL_PRINT_H_
