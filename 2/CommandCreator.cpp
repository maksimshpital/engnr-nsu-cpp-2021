#include "CommandCreator.h"


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
            SafeInt<int64_t> arg;
            try {
                arg = SafeInt<int64_t> (tokens.at(1));
            } catch (...) {
                throw BadInputException("Invalid input");
            }
            creatorWithArg.create(tokens.at(0))->execute(ctx, arg);
        } else {
            creatorWithArg.create(tokens.at(0))->execute(ctx, tokens.at(1));
        }
    }
}

Command* CommandCreatorWithArg::create(const std::string & cmdName) const {
    if(cmdName == "PUSH") {
        return new PushCommand();
    } else if(cmdName == "PEEK") {
        return new PeekCommand();
    } else {
        throw BadCommand("bad command (with arg)");
    }
}


Command* CommandCreatorNoArg::create(const std::string & cmdName) const {
    if(cmdName == "POP") {
        return new PopCommand();
    }else if(cmdName == "ABS") {
        return new AbsCommand();
    }else if(cmdName == "PLUS") {
        return new PlusCommand();
    }else if(cmdName == "MINUS") {
        return new MinusCommand();
    }else if(cmdName == "MUL") {
        return new MulCommand();
    }else if(cmdName == "DIV") {
        return new DivCommand();
    }else if(cmdName == "READ") {
        return new ReadCommand();
    }else if(cmdName == "PRINT") {
        return new PrintCommand();
    }else {
        throw BadCommand("bad command (with no arg)");
    }
}
