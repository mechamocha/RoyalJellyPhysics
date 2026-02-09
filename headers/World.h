#pragma once

#include "Component.h"
#include <unordered_set>

#include "Transforms.h"
#include "RigidBody2D.h"
#include "Colliders.h"

namespace RJPhysics
{
	class World
	{
	private:
		Entity nextEntity;
		std::unordered_set<Entity> alive;

		void IntegrateRigidbodies(fpm::q16_16 dt);
		void ClearForceAccumulators();

		void DoBroadPhase();

	public:
		// collection of entities in the world
		ComponentStorage<Entity> entities;

		// components
		ComponentStorage<Position2D> positions;
		ComponentStorage<RigidBody2D> rigidbodies;
		ComponentStorage<BoxCollider2D> boxColliders;

		Entity CreateEntity();
		void DestroyEntity(Entity e);

		void StepPhysics(fpm::q16_16 dt);
	};
}