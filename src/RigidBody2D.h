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

		fpm::q16_16 invMass;	// Inverse mass of rigidbody in kg, == 1/mass
		Vec2 velocity;		// Direction vector of movement whose magnitude determines the rate of change of displacement
		Vec2 acceleration;
		//fpm::q16_16 drag;	// Decay rate of linear velocity

		bool usesGravity;	// Whether the rigidbody is affected by gravity

		// CONSTRUCTORS
		RigidBody2D() {
			type = BodyType::Dynamic;
			invMass = fpm::q16_16(1);
			velocity = Vec2();
			acceleration = Vec2();
			//drag = 

			usesGravity = true;
		}

		// FUNCTIONS

		// Returns the new acceleration of a rigidbody given the current net force
		Vec2 ForceToAcceleration(Vec2 force, fpm::q16_16 invMass) {
			// F = ma
			Vec2 newAcc = (force * invMass) + (Vec2::Down * fpm::q16_16(9.81)); // +drag +etcetera

			return newAcc;
		}
	};
}