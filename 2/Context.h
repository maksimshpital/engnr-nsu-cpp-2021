#ifndef STACK_CALC_CONTEXT_H
#define STACK_CALC_CONTEXT_H

#include <stack>
#include <string>
#include <map>

class Context {
public:
    std::stack<int> stack;
    std::map<std::string, int> vars;
};


#endif //STACK_CALC_CONTEXT_H
