#pragma once

#include "Vector.h"

namespace RJPhysics
{
	struct BoxCollider2D
	{
		Vec2 size;

		BoxCollider2D() {
			this->size = Vec2(fpm::q16_16(1), fpm::q16_16(1));
		}

		// Get half the length of this collider along the x-axis as a scalar.
		fpm::q16_16 GetXHalfwidth() const {
			return size.x * fpm::q16_16(0.5f);
		}
		// Get half the length of this collider along the y-axis as a scalar.
		fpm::q16_16 GetYHalfwidth() const {
			return size.y * fpm::q16_16(0.5f);
		}
	};
	/*
	struct CircleCollider2D
	{
		fpm::q16_16 radius;

		CircleCollider2D() {
			this->radius = fpm::q16_16(1);
		}
	};
	*/
}