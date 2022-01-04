add_executable(tests
        unit_tests.cpp
        )

target_link_libraries(tests
        gtest
        pthread
        )

target_include_directories(tests
        PRIVATE "../third-party/googletest/googletest/include"
        )

enable_testing()
add_test(NAME googletest COMMAND tests)