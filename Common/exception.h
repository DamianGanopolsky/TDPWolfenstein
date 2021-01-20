#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>
//-------------------------------------------------------------------------------
class Exception: public std::exception {
	std::string message_err;

	public:
		explicit Exception(const std::string& message_err) noexcept;
		virtual const char* what() const noexcept;
		virtual ~Exception() noexcept;
};
#endif
