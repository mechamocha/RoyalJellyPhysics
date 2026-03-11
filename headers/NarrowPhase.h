#pragma once

#include "Component.h"
#include "Vector.h"
#include "Colliders.h"
#include "World.h"

namespace RJPhysics
{
	struct ContactManifold
	{
		Entity a;
		Entity b;

		Vec2 normal;
		fpm::q16_16 penetration;

		Vec2 contactPoints[2];
		int pointCount;	// in case contact has <2 points
	};

	ContactManifold* DetectCollisionAABB_AABB(World& world, std::pair<Entity, Entity> pair);
}