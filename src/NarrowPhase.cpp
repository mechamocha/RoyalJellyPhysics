#include "NarrowPhase.h"

#include <fpm/fixed.hpp>

namespace RJPhysics
{
	// Returns collision status, returns nullptr if no collision.
	ContactManifold* DetectCollisionAABB_AABB(World& world, std::pair<Entity, Entity> pair) {

		const BoxCollider2D& boxA = world.boxColliders.GetComponentReadonly(pair.first);
		const BoxCollider2D& boxB = world.boxColliders.GetComponentReadonly(pair.second);
		const Position2D& posA = world.positions.GetComponentReadonly(pair.first);
		const Position2D& posB = world.positions.GetComponentReadonly(pair.second);

		{
			// detect collision
			fpm::q16_16 aMinY = posA.position.y - boxA.GetYHalfwidth();
			fpm::q16_16 aMaxY = posA.position.y + boxA.GetYHalfwidth();
			fpm::q16_16 bMinY = posB.position.y - boxB.GetYHalfwidth();
			fpm::q16_16 bMaxY = posB.position.y + boxB.GetYHalfwidth();
			if (!(aMinY <= bMaxY && aMaxY >= bMinY)) {
				// not intersecting
				return nullptr;
			}
		}

		// calculate collision normal
		const RigidBody2D& rbA = world.rigidbodies.GetComponentReadonly(pair.first);
		const RigidBody2D& rbB = world.rigidbodies.GetComponentReadonly(pair.second);

		Vec2 pointVelocityDir = Vec2::Normalize(rbB.velocity - rbA.velocity); // unit direction vector of ray

		Vec2 reciprocalDir = Vec2(
			(pointVelocityDir.x != fpm::q16_16(0)) ? (fpm::q16_16(1) / pointVelocityDir.x) : (fpm::q16_16(1) / fpm::fixed_16_16(0.000015f)), // minimum positive value that can be represented
			(pointVelocityDir.y != fpm::q16_16(0)) ? (fpm::q16_16(1) / pointVelocityDir.y) : (fpm::q16_16(1) / fpm::fixed_16_16(0.000015f))
		);

		// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
		Vec2 fixedBox = boxA.size + boxB.size;
		Vec2 lb = Vec2(
			posA.position.x - (fixedBox.x * fpm::q16_16(0.5f)),
			posA.position.y - (fixedBox.y * fpm::q16_16(0.5f))
		);
		Vec2 rt = Vec2(
			posA.position.x + (fixedBox.x * fpm::q16_16(0.5f)),
			posA.position.y + (fixedBox.y * fpm::q16_16(0.5f))
		);
		fpm::q16_16 t1 = (lb.x - posB.position.x) * reciprocalDir.x;
		fpm::q16_16 t2 = (rt.x - posB.position.x) * reciprocalDir.x;
		fpm::q16_16 t3 = (lb.y - posB.position.y) * reciprocalDir.y;
		fpm::q16_16 t4 = (rt.y - posB.position.y) * reciprocalDir.y;
		fpm::q16_16 tmin = std::max(std::min(t1, t2), std::min(t3, t4));
		// this is an AABB-ray intersection algorithm i modified, just to obtain collision normal. 
		// there would be a tmax that gets the minimum of all maximums of each pair
		// and tmin and tmax would be compared to detect collision. however, since
		// collision is already true, i forgo this use tmin to determine the normal.
		Vec2 normal;
		if (tmin == t1) normal = Vec2::Left; /* left */
		else if (tmin == t2) normal = Vec2::Right; /* right */
		else if (tmin == t3) normal = Vec2::Down; /* bottom */
		else if (tmin == t4) normal = Vec2::Up; /* top */



	}
}