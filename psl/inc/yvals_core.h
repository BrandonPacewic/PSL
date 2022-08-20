// yvals_core.h internal header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef YVALS_CORE_H_
#define YVALS_CORE_H_

#ifndef __cplusplus
#pragma message(__FILE__ "("__LINE__"): PSL: Unexpected compiler, expected C++ compiler")
#error Error in C++ PSL usage
#endif // __cplusplus

#if !_HAS_CXX20
#pragma message(__FILE__ "("__LINE__"): PSL: Unexpected compiler, expected C++20 compiler")
#error Error in C++ PSL usage
#endif // !_HAS_CXX20

#define PSL_VERSION_MAJOR 0
#define PSL_VERSION_MINOR 1
#define PSL_VERSION_PATCH 0
#define PSL_VERSION_STRING "0.1.0"

#define PSL_VERSION_CODE (PSL_VERSION_MAJOR * 10000 + PSL_VERSION_MINOR * 100 + PSL_VERSION_PATCH)

#define PSL_BEGIN namespace psl {
#define PSL_END }

#ifdef ENABLE_PSL_INTERNAL_DEBUG
#include <cassert>
#define PSL_INTERNAL_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#else // ^^^ ENABLE_PSL_INTERNAL_DEBUG ^^^ // vvv !ENABLE_PSL_INTERNAL_DEBUG vvv
#define PSL_INTERNAL_STATIC_ASSERT(...)
#endif // ENABLE_PSL_INTERNAL_DEBUG

#endif // YVALS_CORE_H_