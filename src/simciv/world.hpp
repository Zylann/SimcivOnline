#ifndef HEADER_SIMCIV_WORLD_HPP_INCLUDED
#define HEADER_SIMCIV_WORLD_HPP_INCLUDED

#include "common.hpp"
#include "terrain.hpp"

namespace simciv
{

class World
{
public:

	World();
	~World();

	void update(u32 delta);

private:

	Terrain m_terrain;

};

} // namespace simciv

#endif // HEADER_SIMCIV_WORLD_HPP_INCLUDED

