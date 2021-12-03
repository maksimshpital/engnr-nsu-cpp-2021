#include "Command.h"

void PushCommand::execute(Context & ctx, int value) const {
    ctx.stack.push(value);
}

void PushCommand::execute(Context & ctx, const std::string& arg) const {
    auto iter = ctx.vars.find(arg);
    if(iter != ctx.vars.end()) {
        ctx.stack.push(iter->second);
    } else {
        throw NotFoundInputException("variable not found");
    }
}

void PeekCommand::execute(Context & ctx, const std::string& arg) const {
    auto iter = ctx.vars.find(arg);
    if(iter != ctx.vars.end()) {
        iter->second = ctx.stack.top();
    }else {
        ctx.vars.insert(std::make_pair(arg, ctx.stack.top()));
    }
}

void PopCommand::execute(Context & ctx) const {
    if(ctx.stack.empty()) {
        throw EmptyStack("Stack is empty");
    }
    ctx.stack.pop();
}

void AbsCommand::execute(Context & ctx) const {
    if(ctx.stack.empty()) {
        throw EmptyStack("Stack is empty");
    }
    try{
        SafeInt<int> value = ctx.stack.top();
        ctx.stack.pop();
        if(value > 0){
            ctx.stack.push(value);
        }else {
            ctx.stack.push(-value);
        }
    }catch (...) {
        throw OverflowException("Overflow detected in ABS command");
    }
}


void PlusCommand::execute(Context & ctx) const {
    if(ctx.stack.size() < 2) {
        throw IncorrectStackDepth("PlusCommand: stack size < 2");
    }

    int val_1 = ctx.stack.top();
    ctx.stack.pop();
    int val_2 = ctx.stack.top();
    ctx.stack.pop();
    int result;
    if(!SafeAdd(val_1, val_2, result)){
        throw OverflowException("Overflow detected in PLUS command");
    }else {
        ctx.stack.push(result);
    }
}

void MinusCommand::execute(Context & ctx) const {
    if(ctx.stack.size() < 2) {
        throw IncorrectStackDepth("MinusCommand: stack size < 2");
    }
    int val_1 = ctx.stack.top();
    ctx.stack.pop();
    int val_2 = ctx.stack.top();
    ctx.stack.pop();
    int result;
    if(!SafeSubtract(val_2, val_1, result)) {
        throw OverflowException("Overflow detected in MINUS command");
    }else{
        ctx.stack.push(result);
    }
}

void MulCommand::execute(Context & ctx) const {
    if(ctx.stack.size() < 2) {
        throw IncorrectStackDepth("MulCommand: stack size < 2");
    }
    int val_1 = ctx.stack.top();
    ctx.stack.pop();
    int val_2 = ctx.stack.top();
    ctx.stack.pop();
    int result;
    if(!SafeMultiply(val_1, val_2, result)) {
        throw OverflowException("Overflow detected in MULTIPLE command");
    } else {
        ctx.stack.push(result);
    }
}

void DivCommand::execute(Context & ctx) const {
    if(ctx.stack.size() < 2) {
        throw IncorrectStackDepth("DivCommand: stack size < 2");
    }
    int val_1 = ctx.stack.top();
    ctx.stack.pop();
    int val_2 = ctx.stack.top();
    ctx.stack.pop();
    int result;
    if(!SafeDivide(val_2, val_1, result)) {
        throw OverflowException("Overflow detected in DIVIDE command");
    }else {
        ctx.stack.push(result);
    }
}

void ReadCommand::execute(Context & ctx) const {
    std::string str_value;
    std::cout << "num> ";
    std::getline(std::cin, str_value);
    try{
        SafeInt<int> int_value = std::stoi(str_value);
        ctx.stack.push(int_value);
    }catch (...) {
        throw OverflowException("Invalid number detected...");
    }
}

void PrintCommand::execute(Context & ctx) const {
    if(ctx.stack.empty()) {
        throw EmptyStack("stack is empty");
    }
    std::cout << ctx.stack.top() << std::endl;
}
