#ifndef STACK_CALC_HELPER_H
#define STACK_CALC_HELPER_H

#include <iostream>
#include <vector>
#include <string>

namespace helper {
    std::vector<std::string> split(std::string, const std::string&);
    bool isDigit(const std::string&);
    std::string strip(std::string);
}

#endif //STACK_CALC_HELPER_H
