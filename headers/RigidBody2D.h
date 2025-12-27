#pragma once

#include "Vector.h"
//#include "Colliders.h"

namespace RJPhysics
{
	struct RigidBody2D
	{
		enum class BodyType
		{
			Dynamic,
			Static
		};
		BodyType type;

		fpm::q16_16 invMass;	// Inverse mass of rigidbody in kg, == 1/mass
		Vec2 velocity;		// Direction vector of movement whose magnitude determines the rate of change of displacement
		Vec2 acceleration;
		//fpm::q16_16 drag;	// Decay rate of linear velocity

		// accumulates net forces, to be cleared at the start of each frame
		Vec2 forceAccumulator;

		bool usesGravity;	// Whether the rigidbody is affected by gravity

		// CONSTRUCTORS
		RigidBody2D() {
			type = BodyType::Dynamic;
			invMass = fpm::q16_16(1);
			velocity = Vec2();
			acceleration = Vec2();

			forceAccumulator = Vec2();

			usesGravity = true;
		}
		RigidBody2D(BodyType type){
			this->type = type;
			if (type == BodyType::Dynamic){
				invMass = fpm::q16_16(1);
				usesGravity = true;
			}
			else {
				// static == unaffected by forces
				invMass = fpm::q16_16(0);
				usesGravity = false;
			}
			velocity = Vec2();
			acceleration = Vec2();

			forceAccumulator = Vec2();
		}

		// FUNCTIONS

		void AddForce(Vec2 force){
			forceAccumulator += force;
		}

		// Returns the new acceleration of a rigidbody given the current net force
		Vec2 ForceToAcceleration(Vec2 force) {
			// F = ma
			Vec2 newAcc = (force * this->invMass); // +drag +etcetera
			if (this->usesGravity) {
				newAcc + (Vec2::Down * fpm::q16_16(9.81));
			}

			return newAcc;
		}

		void Integrate(fpm::q16_16 dt, Position2D& pos) {
			Vec2 newPos = pos.position + (this->velocity * dt) + this->acceleration * (dt * dt * fpm::q16_16(0.5));
			Vec2 newAcc = ForceToAcceleration(forceAccumulator);
			Vec2 newVel = this->velocity + (this->acceleration + newAcc) * (dt * fpm::q16_16(0.5));
			pos.position = newPos;
			this->velocity = newVel;
			this->acceleration = newAcc;
		}
	};
}