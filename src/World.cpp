#include "World.h"

namespace RJPhysics
{
	// returns the id of the entity
	Entity World::CreateEntity() {
		Entity id = nextEntity++;
		alive.insert(id);
		return id;
	}
	void World::DestroyEntity(Entity e) {
		alive.erase(e);
		positions.Remove(e);
		rigidbodies.Remove(e);
		boxColliders.Remove(e);
	}
}