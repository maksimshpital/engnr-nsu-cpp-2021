#ifndef STACK_CALC_CONTEXT_H
#define STACK_CALC_CONTEXT_H

#include <stack>
#include <string>
#include <map>
#include "third-party/SafeInt/SafeInt.hpp"

class Context {
public:
    std::stack<SafeInt<int64_t>> stack;
    std::map<std::string, SafeInt<int64_t>> vars;
};


#endif //STACK_CALC_CONTEXT_H
