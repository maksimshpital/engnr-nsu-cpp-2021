#ifndef STACK_CALC_HELPER_H
#define STACK_CALC_HELPER_H


#pragma once

#include <iostream>
#include <vector>
#include <string>

class Helper {
public:
    static std::vector<std::string> split(std::string, const std::string&);
    static bool isDigit(const std::string&);
    static std::string strip(std::string);
};

#endif //STACK_CALC_HELPER_H
