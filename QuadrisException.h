#ifndef QUADRIS_EXCEPTION_H
#define QUADRIS_EXCEPTION_H

#include <stdexcept>
#include <string>

class QuadrisException : public std::runtime_error {
public:
	QuadrisException(const std::string &what_arg = "");
};

#endif

