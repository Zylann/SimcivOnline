#include "world.hpp"
#include "entity.hpp"

namespace simciv
{

//------------------------------------------------------------------------------
World::~World()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		delete (*it);
	}
}

//------------------------------------------------------------------------------
void World::update(u32 delta)
{
	time += delta;

	auto entitiesCopy = entities;
	for (auto it = entitiesCopy.begin(); it != entitiesCopy.end(); ++it)
	{
		(*it)->update(delta);
	}
}

//------------------------------------------------------------------------------
Entity * World::spawn(Entity *newEntity)
{
	entities.push_back(newEntity);
	newEntity->id = entities.size() - 1;
	newEntity->onCreate();
	return newEntity;
}

} // namespace simciv


