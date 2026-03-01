#include "BroadPhase.h"
#include <algorithm>
#include <cstdint>

namespace RJPhysics
{
	// Initialise the SAP cache
	void SweepAndPrune::Build(World& world) {
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
	void SweepAndPrune::Update(World& world) {
		// update positions and sizes of all the colliders
		for (SAPEntry e : cache) {
			e = SAPEntry(e.entity, world);
		}

		// Insertion sort is fast if the list is nearly sorted
		for (int32_t i = 1; i < cache.size(); i++) {
			SAPEntry key = cache[i]; // get current element (starting from second element)
			int32_t j = i - 1; // get preceeding element

			// if preceeding element has bigger minX, shift it to the right and check the next preceeding element until sorted
			while (j >= 0 && cache[j].minX > key.minX) {
				cache[j+1] = cache[j];
				j--;
			}

			cache[j+1] = key; // place the current element in sorted position
		}
	}

	// Group colliders to check during narrow phase
	void SweepAndPrune::GroupPairs() {
		pairs.clear();

		for (int32_t i = 0; i < cache.size(); i++) {
			const SAPEntry& a = cache[i];

			// check each subsequent entry for overlap
			for (int32_t j = i + 1; j < cache.size(); j++) {
				const SAPEntry& b = cache[j];

				// does not overlap
				if (b.minX > a.maxX)
					break; // no more possible overlaps

				// does overlap, add pair for narrow phase to check
				pairs.emplace_back(a.entity, b.entity);
			}
		}
	}
}
