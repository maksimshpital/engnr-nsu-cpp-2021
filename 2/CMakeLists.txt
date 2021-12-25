cmake_minimum_required(VERSION 3.10)
project(stack_calc)
add_subdirectory(third-party/SafeInt)
add_subdirectory(third-party/googletest)

set(CMAKE_CXX_STANDARD 14)

add_executable (
        stack_calc
        main.cpp
        Helper.h
        Helper.cpp
        Command.h
        Context.h
	CommandCreator.h
        CommandCreator.cpp
        AppException.cpp
)

target_include_directories (stack_calc
            PUBLIC third-party/SafeInt
            PUBLIC trird-party/googletest/googletest/include/gtest
)

if (MSVC)
    target_compile_options(stack_calc
            PRIVATE /W3          #  warnings level
            PRIVATE /WX          #  treat all warnings as errors
            )
else()
    target_compile_options(stack_calc
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -Werror      # treat all warnings as errors
            )
endif()