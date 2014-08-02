#ifndef HEADER_SIMCIV_TERRAIN_HPP_INCLUDED
#define HEADER_SIMCIV_TERRAIN_HPP_INCLUDED

#include <fm/util/Array2D.hpp>
#include "common.hpp"

namespace simciv
{

class Terrain
{
public:

	enum GroundTypes
	{
		G_VOID = 0,
		G_ROCK = 1,
		G_DUST = 2,
		G_GRASS = 3,
		G_WATER = 4
	};

	Terrain();
	~Terrain();

	Array2D<u8> ground;
};

} // namespace simciv

#endif // HEADER_SIMCIV_TERRAIN_HPP_INCLUDED

