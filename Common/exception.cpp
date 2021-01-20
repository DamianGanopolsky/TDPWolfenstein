#include "./exception.h"
//-------------------------------------------------------------------------------
Exception::Exception(const std::string& message_err) noexcept : 
													message_err(message_err) {}

const char* Exception::what() const noexcept {
	return message_err.c_str();
}
Exception::~Exception() noexcept {}
