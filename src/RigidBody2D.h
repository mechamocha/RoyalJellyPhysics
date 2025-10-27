#pragma once

#include "Vector.h"
#include "Colliders.h"

namespace RJPhysics
{
	struct RigidBody2D
	{
		enum class BodyType
		{
			Dynamic,
			Kinematic
		};
		BodyType type;

		fpm::q16_16 mass;	// Mass of rigidbody in kg
		Vec2 velocity;		// Direction vector of movement whose magnitude determines the rate of change of displacement
		Vec2 acceleration;
		//fpm::q16_16 drag;	// Decay rate of linear velocity

		bool usesGravity;	// Whether the rigidbody is affected by gravity

		// CONSTRUCTORS
		RigidBody2D() {
			type = BodyType::Dynamic;
			mass = fpm::q16_16(1);
			velocity = Vec2();
			acceleration = Vec2();
			//drag = 

			usesGravity = true;
		}

		// FUNCTIONS

	};
}