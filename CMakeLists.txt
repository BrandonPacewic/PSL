# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(psl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(psl)
