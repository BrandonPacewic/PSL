# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/inc/List
    ${CMAKE_CURRENT_LIST_DIR}/inc/yvals_core.h
)

foreach(header ${HEADERS})
    file(RELATIVE_PATH _header_path "${CMAKE_CURRENT_LIST_DIR}/inc" "${header}")
    configure_file("${header}" "${PROJECT_BINARY_DIR}/out/inc/${_header_path}" COPYONLY)
endforeach()

include_directories(BEFORE "${CMAKE_CURRENT_LIST_DIR}/inc")
