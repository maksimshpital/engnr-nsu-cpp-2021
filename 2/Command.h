#ifndef STACK_CALC_COMMAND_H
#define STACK_CALC_COMMAND_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Context.h"
#include "AppException.h"
#include "SafeInt.hpp"


class Command {
public:
    virtual void execute(Context&) const {};
    virtual void execute(Context&, int) const {};
    virtual void execute(Context&, const std::string&) const {};
};

class PushCommand : public Command {
public:
    void execute(Context&, int) const override ;
    void execute(Context&, const std::string&) const override;
};

class PeekCommand : public Command {
public:
    void execute(Context&, const std::string&) const override;
};

class PopCommand : public Command {
public:
    void execute(Context&) const override;
};

class AbsCommand : public Command {
public:
    void execute(Context&) const override;
};

class PlusCommand : public Command {
public:
    void execute(Context&) const override;
};

class MinusCommand : public Command {
public:
    void execute(Context&) const override;
};

class MulCommand : public Command {
public:
    void execute(Context&) const override;
};

class DivCommand : public Command {
public:
    void execute(Context&) const override;
};

class ReadCommand : public Command {
public:
    void execute(Context&) const override;
};

class PrintCommand : public Command {
public:
    void execute(Context&) const override;
};

#endif //STACK_CALC_COMMAND_H

