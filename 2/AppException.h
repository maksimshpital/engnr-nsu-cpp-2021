#ifndef STACK_CALC_APPEXCEPTION_H
#define STACK_CALC_APPEXCEPTION_H


#include <string>


class AppException : std::exception{
private:
    std::string m_error;
public:
    AppException(std::string& err){
        m_error = err;
    }
    const char* what() const noexcept override {
        return m_error.c_str();
    }
    void setError(std::string& msg){
        m_error = msg;
    }
};


class InputException : public AppException {
public:
    InputException(std::string& err) : AppException(err) {
        std::string error("Input Exception: " + err);
        setError(error);
    }
};

class ContextException : public AppException {
public:
    ContextException(std::string& err) : AppException(err){
        std::string error("Context Exception: " + err);
        setError(error);
    }
};

class CommandException : public AppException {
public:
    CommandException(std::string& err) : AppException(err) {
        std::string error("Command Exception: " + err);
        setError(error);
    }
};


class BadInputException : public InputException {
public:
    BadInputException(std::string err) : InputException(err){}
};

class NotFoundInputException : public InputException {
public:
    NotFoundInputException(std::string err) : InputException(err){}
};


class OverflowException : public ContextException {
public:
    OverflowException(std::string err) : ContextException(err){}
};

class EmptyStack : public ContextException {
public:
    EmptyStack(std::string err) : ContextException(err){}
};

class IncorrectStackDepth : public ContextException {
public:
    IncorrectStackDepth(std::string err) : ContextException(err){}
};

class BadCommand : public CommandException {
public:
    BadCommand(std::string err) : CommandException(err){}
};

#endif //STACK_CALC_APPEXCEPTION_H
