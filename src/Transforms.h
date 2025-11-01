#pragma once

#include "Vector.h"

namespace RJPhysics
{
	struct Position2D
	{
		Vec2 position; // current position
		//Vec2 oldPos; // previous frame position for verlet integration
		Position2D() {
			this->position = Vec2();
			//this->oldPos = this->position;
		}
	};

}