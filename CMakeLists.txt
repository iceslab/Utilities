cmake_minimum_required (VERSION 2.6)
project (Utilities)
add_library (Utilites Timer.cpp Timer.h asserts.h)
target_include_directories (Utilites PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
