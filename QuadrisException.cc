#include "QuadrisException.h"

QuadrisException::QuadrisException(const std::string &what_arg)
	: std::runtime_error(what_arg) {}

