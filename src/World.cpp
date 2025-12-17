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

	// Integrate the positions of all rigidbodies WORK IN PROGRESS
	void World::IntegrateDynamicRigidbodies(fpm::q16_16 dt) {
		for (int i = 0; i < rigidbodies.components.size(); i++) {
			// ensure this entity has position
			if (!positions.Has(rigidbodies.entities[i])) continue;

			// the components and entities vectors have corresponding indices TEMPORARY NET FORCE
			rigidbodies.components[i].Integrate(
				dt,
				positions.GetComponent(rigidbodies.entities[i]),
				RJPhysics::Vec2(fpm::q16_16(0), fpm::q16_16(-9.81))
			);
		}
	}

}