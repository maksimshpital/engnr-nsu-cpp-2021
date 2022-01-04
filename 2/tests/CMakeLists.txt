
add_executable(run_tests unit_tests.cpp
../AppException.cpp
../AppException.h
../Command.cpp
../Command.h
../CommandCreator.cpp
../CommandCreator.h
../Context.h
../Helper.cpp
../Helper.h
../third-party/SafeInt/SafeInt.hpp)

target_link_libraries(run_tests gtest pthread)

target_include_directories(run_tests
PRIVATE "../third-party/googletest/googletest/include/gtest"
)

enable_testing()
add_test(NAME unit_tests COMMAND run_tests)