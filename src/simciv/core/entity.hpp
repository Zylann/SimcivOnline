#include <fm/util/Vector2.hpp>
#include "simciv/common.hpp"
#include "simciv/core/world.hpp"

namespace simciv
{

class Entity
{
public:

	Entity() :
		id(0),
		createTime(0),
		world(nullptr),
		tickTime(500),
		timeBeforeTick(0)
	{
	}

	virtual ~Entity()
	{}

	virtual void onCreate() {}
	virtual void onDestroy() {}

	virtual void update(u32 delta);
	virtual void tick() {}

	inline const Vector2i & position() { return m_position; }
	void setPosition(const Vector2i pos);

	u32 id;
	u64 createTime;
	World * world;
	u32 tickTime;
	s32 timeBeforeTick;

private:

	Vector2i m_position;

};

} // namespace simciv

