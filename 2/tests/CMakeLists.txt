

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
