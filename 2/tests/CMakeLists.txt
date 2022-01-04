
add_executable(tests unit_tests.cpp
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

target_link_libraries(tests gtest pthread)

target_include_directories(tests
PRIVATE "../third-party/googletest/googletest/include/gtest"
)

enable_testing()
add_test(NAME googletest COMMAND tests)