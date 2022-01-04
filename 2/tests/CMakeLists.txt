add_executable(run_tests
        unit_tests.cpp
        )

target_link_libraries(run_tests
        tests
        gtest
        pthread
        )

target_include_directories(run_tests
        PRIVATE "../third-party/googletest/googletest/include"
        )

enable_testing()
add_test(NAME googletest COMMAND run_tests)