#include "Util.h"

#include <sstream>
#include <string>

std::string operator+(std::string& a, int b)
{
	std::ostringstream oss;
	oss << a << b;
	return oss.str();
}
