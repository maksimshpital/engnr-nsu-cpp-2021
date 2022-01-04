#include <memory>
#include "CommandCreator.h"
#include "third-party/SafeInt/SafeInt.hpp"

std::unique_ptr<Command> CommandCreator::create(const std::string& str) const {
    return std::unique_ptr<Command> (nullptr);
}

void CommandCreator::proceed(std::string& line, Context& ctx) {
    if (line.empty() || line.at(0) == '#' || line.at(0) == '\r') {
        return;
    }

    std::vector<std::string> tokens = helper::split(line, " ");
    if (tokens.size() == 1) {
        CommandCreatorNoArg creatorNoArg;
        creatorNoArg.create(tokens.at(0))->execute(ctx);
    } else if (tokens.size() == 2) {
        CommandCreatorWithArg creatorWithArg;
        if(helper::isDigit(tokens.at(1))) {
            try {
                SafeInt<int64_t> arg = SafeInt<int64_t>::SafeAtoI(tokens.at(1).c_str());
                creatorWithArg.create(tokens.at(0))->execute(ctx, arg);
            } catch (...) {
                throw BadInputException("Invalid input");
            }
        } else {
            creatorWithArg.create(tokens.at(0))->execute(ctx, tokens.at(1));
        }
    }
}

std::unique_ptr<Command> CommandCreatorWithArg::create(const std::string & cmdName) const {
    if(cmdName == "PUSH") {
        return std::make_unique<PushCommand> ();
    } else if(cmdName == "PEEK") {
        return std::make_unique<PeekCommand> ();
    } else {
        throw BadCommand("bad command (with arg)");
    }
}


std::unique_ptr<Command> CommandCreatorNoArg::create(const std::string & cmdName) const {
    if(cmdName == "POP") {
        return std::make_unique<PopCommand> ();
    }else if(cmdName == "ABS") {
        return std::make_unique<AbsCommand> ();
    }else if(cmdName == "PLUS") {
        return std::make_unique<PlusCommand> ();
    }else if(cmdName == "MINUS") {
        return std::make_unique<MinusCommand> ();
    }else if(cmdName == "MUL") {
        return std::make_unique<MulCommand> ();
    }else if(cmdName == "DIV") {
        return std::make_unique<DivCommand> ();
    }else if(cmdName == "READ") {
        return std::make_unique<ReadCommand> ();
    }else if(cmdName == "PRINT") {
        return std::make_unique<PrintCommand> ();
    }else {
        throw BadCommand("bad command (with no arg)");
    }
}
