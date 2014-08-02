#include <sstream>
#include "version.hpp"

namespace simciv {
namespace version {

std::string asString()
{
	std::stringstream ss;
	ss << version[0] << "." << version[1] << "." << version[2];
	ss << " (" << stage << ")";
	return ss.str();
}

} // namespace version
} // namespace simciv


