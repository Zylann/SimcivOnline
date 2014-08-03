#include "entity.hpp"

namespace simciv
{

//------------------------------------------------------------------------------
void Entity::update(u32 delta)
{
	timeBeforeTick -= delta;
	if (timeBeforeTick <= 0)
	{
		timeBeforeTick += tickTime;
		tick();
	}
}

//------------------------------------------------------------------------------
void Entity::setPosition(const Vector2i pos)
{
	m_position = pos;
}

} // namespace simciv

