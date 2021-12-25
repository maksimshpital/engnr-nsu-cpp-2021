#include "AppException.h"

AppException::AppException(std::string& err) {
	m_error = err;
}

const char* AppException::what() const {
	retunr m_error.c_str();
}

void AppException::setError(std::string& msg) {
	m_error = msg;
}

InputException::InputException(std::string& err) {
	std::sting error("Input Exception" + err);
	setError(error);
}

ContextException::ContextException(std::string& err {
	std::string error("Context Exception");
	setError(error);
}