#ifndef STACK_CALC_APPEXCEPTION_H
#define STACK_CALC_APPEXCEPTION_H

#include <string>

class AppException : std::exception {
private:
    std::string m_error;
public:
    AppException(std::string& err) : m_error(err) {}

    const char* what() const noexcept;

    void setError(std::string& msg);

    virtual ~AppException() {}
};


class InputException : public AppException {
public:
    InputException(std::string& err);

    virtual ~InputException() {}
};

class ContextException : public AppException {
public:
    ContextException(std::string& err);

    virtual ~ContextException() {}
};

class CommandException : public AppException {
public:
    CommandException(std::string& err);

    virtual ~CommandException() {}
};


class BadInputException : public InputException {
public:
    BadInputException(std::string& err) : InputException(err) {}

    virtual ~BadInputException() {}
};

class NotFoundInputException : public InputException {
public:
    NotFoundInputException(std::string& err) : InputException(err) {}

    virtual ~NotFoundInputException() {}
};

class OverflowException : public ContextException {
public:
    OverflowException(std::string& err) : ContextException(err) {}

    virtual ~OverflowException() {}
};

class EmptyStack : public ContextException {
public:
    EmptyStack(std::string& err) : ContextException(err) {}

    virtual ~EmptyStack() {}
};

class IncorrectStackDepth : public ContextException {
public:
    IncorrectStackDepth(std::string& err) : ContextException(err) {}

    virtual ~IncorrectStackDepth() {}
};

class BadCommand : public CommandException {
public:
    BadCommand(std::string& err) : CommandException(err) {}

    virtual ~BadCommand() {}
};

#endif //STACK_CALC_APPEXCEPTION_H
