#ifndef HEADER_SIMCIV_VERSION_HPP_INCLUDED
#define HEADER_SIMCIV_VERSION_HPP_INCLUDED

#include "common.hpp"

namespace simciv {
namespace version {

static const u32 version[3] = {0, 1, 0};
static const char * stage = "indev";

std::string asString();

} // namespace version
} // namespace simciv

#endif // HEADER_SIMCIV_VERSION_HPP_INCLUDED

