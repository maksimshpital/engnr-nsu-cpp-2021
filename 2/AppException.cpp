#include "AppException.h"

const char* AppException::what() const {
	retunr m_error.c_str();
}

void AppException::setError(std::string& msg) {
	m_error = msg;
}

InputException::InputException(std::string& err) : AppException(err) {
	std::sting error("Input Exception" + err);
	setError(error);
}

ContextException::ContextException(std::string& err) : AppException(err) {
	std::string error("Context Exception" + err);
	setError(error);
}

CommandException::CommandException(std::string& err) : AppException(err) {
	std::string error("Command Exception" + err);
	setError(error);
}