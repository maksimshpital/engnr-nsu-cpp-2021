#ifndef STACK_CALC_COMMANDCREATOR_H
#define STACK_CALC_COMMANDCREATOR_H

#include "Command.h"
#include "Helper.h"
#include "Context.h"
#include "AppException.h"
#include "SafeInt.hpp"


class CommandCreator {
private:
    virtual Command* create(const std::string&) const { return nullptr; };
public:
    void proceed(std::string&, Context&);
};

class CommandCreatorWithArg : public CommandCreator {
public:
    Command* create(const std::string&) const override;
};

class CommandCreatorNoArg : public CommandCreator {
public:
    Command* create(const std::string&) const override;
};

#endif //STACK_CALC_COMMANDCREATOR_H
