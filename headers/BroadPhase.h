#pragma once

#include<vector>
#include "World.h"
#include "Component.h"
#include "Transforms.h"
#include "Colliders.h"

namespace RJPhysics
{
	

	struct SweepAndPrune
	{
		struct SAPEntry
		{
			Entity entity;
			fpm::q16_16 minX, maxX;

			SAPEntry(Entity e, World& w) {
				entity = e;
				Position2D& pos = w.positions.GetComponent(e);
				BoxCollider2D& box = w.boxColliders.GetComponent(e);

				minX = pos.position.x - box.GetXHalfwidth();
				maxX = pos.position.x + box.GetXHalfwidth();
			}
		};
		std::vector<SAPEntry> cache;

		void Build(const World& world);
		void Update(const World& world);
	};
}