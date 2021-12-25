#ifndef STACK_CALC_COMMAND_H
#define STACK_CALC_COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include "Context.h"
#include "AppException.h"
#include "SafeInt.hpp"


class Command {
public:
    virtual void execute(Context&) const = 0;
    virtual void execute(Context&, int64_t) const  = 0;
    virtual void execute(Context&, const std::string&) const = 0;
};

class PushCommand : public Command {
public:
    void execute(Context&, int64_t) const;
    void execute(Context&, const std::string&) const;

    virtual ~PushCommand() {}
};

class PeekCommand : public Command {
public:
    void execute(Context&, const std::string&) const;

    virtual ~PeekCommand() {}
};

class PopCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~PopCommand() {}
};

class AbsCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~AbsCommand() {}
};

class PlusCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~PlusCommand() {}
};

class MinusCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~MinusCommand() {}
};

class MulCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~MulCommand() {}
};

class DivCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~DivCommand() {}
};

class ReadCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~ReadCommand() {}
};

class PrintCommand : public Command {
public:
    void execute(Context&) const;

    virtual ~PrintCommand() {}
};

#endif //STACK_CALC_COMMAND_H

