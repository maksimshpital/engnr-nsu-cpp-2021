#include "Command.h"

void PushCommand::execute(Context & ctx, SafeInt<int64_t> value) const {
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
        SafeInt<int64_t> value = ctx.stack.top();
        ctx.stack.pop();
        if (value > 0){
            ctx.stack.push(value);
        } else {
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

    SafeInt<int64_t> val_1 = ctx.stack.top();
    ctx.stack.pop();
    SafeInt<int64_t> val_2 = ctx.stack.top();
    ctx.stack.pop();

    ctx.stack.push(val_1 + val_2);
}

void MinusCommand::execute(Context & ctx) const {
    if (ctx.stack.size() < 2) {
        throw IncorrectStackDepth("MinusCommand: stack size < 2");
    }

    SafeInt<int64_t> val_1 = ctx.stack.top();
    ctx.stack.pop();
    SafeInt<int64_t> val_2 = ctx.stack.top();
    ctx.stack.pop();
    
    ctx.stack.push(val_2 - val_1);
}

void MulCommand::execute(Context & ctx) const {
    if (ctx.stack.size() < 2) {
        throw IncorrectStackDepth("MulCommand: stack size < 2");
    }

    SafeInt<int64_t> val_1 = ctx.stack.top();
    ctx.stack.pop();
    SafeInt<int64_t> val_2 = ctx.stack.top();
    ctx.stack.pop();

    ctx.stack.push(val_1 * val_2);
}

void DivCommand::execute(Context & ctx) const {
    if (ctx.stack.size() < 2) {
        throw IncorrectStackDepth("DivCommand: stack size < 2");
    }

    SafeInt<int64_t> val_1 = ctx.stack.top();
    ctx.stack.pop();
    SafeInt<int64_t> val_2 = ctx.stack.top();
    ctx.stack.pop();

    ctx.stack.push(val_2 / val_1);
}

void ReadCommand::execute(Context & ctx) const {
    std::string str_value;
    std::cout << "num> ";
    std::getline(std::cin, str_value);
    SafeInt<int64_t> value = SafeInt<int64_t>::SafeAtoI(str_value.c_str());
    ctx.stack.push(value);
}

void PrintCommand::execute(Context & ctx) const {
    if (ctx.stack.empty()) {
        throw EmptyStack("stack is empty");
    }
    std::cout << *(ctx.stack.top().data_ptr()) << std::endl;
}
