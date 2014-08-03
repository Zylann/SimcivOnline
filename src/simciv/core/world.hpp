#ifndef HEADER_SIMCIV_WORLD_HPP_INCLUDED
#define HEADER_SIMCIV_WORLD_HPP_INCLUDED

#include <vector>
#include "simciv/common.hpp"
#include "simciv/core/terrain.hpp"

namespace simciv
{

class Entity;

class World
{
public:

	World() :
		time(0)
	{}

	~World();

	void update(u32 delta);

	template<class Entity_T>
	Entity_T * spawn()
	{
		Entity_T * e = new Entity_T();
		e->world = this;
		spawn(e);
		return e;
	}

	Entity * spawn(Entity *newEntity);

	u64 time;
	Terrain terrain;
	std::vector<Entity*> entities;

};

} // namespace simciv

#endif // HEADER_SIMCIV_WORLD_HPP_INCLUDED

