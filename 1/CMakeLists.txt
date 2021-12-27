cmake_minimum_required (VERSION 3.1)

project(hasher)


#
# library with common functions for tests and exe
#
add_library(hashlib
            src/hasher/hasher.cpp
            src/hasher/hasher.h)

set_target_properties(hashlib PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

#
# project itself
#
add_executable(hasher src/main.cpp)

set_target_properties(hasher PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

add_dependencies(hasher hashlib)
target_link_libraries(hasher hashlib)