#ifndef STACK_CALC_COMMANDCREATOR_H
#define STACK_CALC_COMMANDCREATOR_H

#include "Command.h"
#include "Helper.h"
#include "Context.h"
#include "AppException.h"
#include "SafeInt.hpp"

class CommandCreator {
private:
    virtual Command* create(const std::string&) const = 0;
public:
    void proceed(std::string&, Context&);
};

class CommandCreatorWithArg : public CommandCreator {
public:
    Command* create(const std::string&) const;

    virtual ~CommandCreatorWithArg() {}
};

class CommandCreatorNoArg : public CommandCreator {
public:
    Command* create(const std::string&) const;

    virtual ~CommandCreatorNoArg() {}
};

#endif //STACK_CALC_COMMANDCREATOR_H
