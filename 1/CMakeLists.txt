cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_1 main.cpp other.h func.cpp)

if (MSVC)
    target_compile_options(lab_1
            PRIVATE /W4
            PRIVATE /WX
            )
else()
    target_compile_options(lab_1
            PRIVATE -Wall
            PRIVATE -pedantic
            PRIVATE -Werror
            )
endif()