add_executable(stack_calc
        unit_tests.cpp
        )

target_link_libraries(stack_calc
        tests
        gtest
        pthread
        )

target_include_directories(stack_calc
        PRIVATE "../third-party/googletest/googletest/include"
        )

enable_testing()
add_test(NAME googletest COMMAND stack_calc)