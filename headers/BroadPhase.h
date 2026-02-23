#pragma once

#include<vector>
#include "Component.h"

namespace RJPhysics
{
	struct SAPEntry
	{
		Entity entity;
		float minX, maxX;
	};

	struct SweepAndPrune
	{
		std::vector<SAPEntry> cache;

	};
}