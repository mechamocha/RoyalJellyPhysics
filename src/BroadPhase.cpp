#include "BroadPhase.h"
#include <algorithm>

namespace RJPhysics
{
	void SweepAndPrune::Build(const World& world) {
		cache.clear();

		for (Entity e : world.boxColliders.GetAllEntities()) {
			if (!world.positions.Has(e)) continue;

			cache.push_back(SAPEntry(e, world));
		}

		// tbh not sure if stable sorting is needed but ill err on the side of caution
		std::stable_sort(cache.begin(), cache.end(),
			[](const SAPEntry& a, const SAPEntry& b) {
				return a.minX < b.minX;
			});
	}

	// Update collider sorting
	void SweepAndPrune::Update(const World& world) {
		for (SAPEntry e : cache) {
			e = SAPEntry(e.entity, world);
		}
	}
}
