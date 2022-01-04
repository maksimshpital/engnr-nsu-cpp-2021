#ifndef STACK_CALC_COMMANDCREATOR_H
#define STACK_CALC_COMMANDCREATOR_H

#include <memory>

#include "Command.h"
#include "Helper.h"
#include "Context.h"
#include "AppException.h"
#include "third-party/SafeInt/SafeInt.hpp"

class CommandCreator {
protected:
    virtual std::unique_ptr<Command> create(const std::string&) const;
public:
    void proceed(std::string&, Context&);

    virtual ~CommandCreator () {} 
};

class CommandCreatorWithArg : public CommandCreator {
public:
    virtual std::unique_ptr<Command> create(const std::string&) const;

    virtual ~CommandCreatorWithArg() {}
};

class CommandCreatorNoArg : public CommandCreator {
public:
    virtual std::unique_ptr<Command> create(const std::string&) const;

    virtual ~CommandCreatorNoArg() {}
};

#endif //STACK_CALC_COMMANDCREATOR_H
