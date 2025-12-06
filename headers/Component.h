#pragma once

#include <cstdint>
#include "Transforms.h"
#include <vector>
#include <unordered_map>

namespace RJPhysics
{
	// Handle to group components
	using Entity = uint32_t;
	constexpr uint32_t INVALID_ENTITY = UINT32_MAX;
	
	// Component storage type
	template <typename T>
	struct ComponentStorage
	{
		// component at index n should be attached to entity at index n
		std::vector<T> components;
		std::vector<Entity> entities;
		std::unordered_map<Entity, size_t> entityToIndex; // allows searching for index at O(1) instead of O(n) loop

		// OPERATIONS

		// Checks if an entity has this component type
		bool Has(Entity e) {
			return entityToIndex.count(e) > 0;
		}

		// Adds a component to the entity. Does nothing if entity already has component.
		void Add(Entity e, const T& component) {
			if (Has(e)) {
				// entity already has component
				return;
			}
			entityToIndex[e] = components.size();
			components.push_back(component);
			entities.push_back(e);
		}

		// Removes a component from the entity
		void Remove(Entity e) {

			// return if the entity already does not have the component
			auto it = entityToIndex.find(e);
			if (it == entityToIndex.end()) return;

			// get the indices of the component to remove and the last component in list
			size_t index = it->second;
			size_t last = components.size() - 1;

			// swap them as it is faster, to pop without shifting all elements down
			if (index != last) {
				std::swap(components[index], components[last]);
				std::swap(entities[index], entities[last]);
				entityToIndex[entities[index]] = index;
			}

			components.pop_back();
			entities.pop_back();
			entityToIndex.erase(it);
		}

		// Gets the component belonging to an Entity, returns std::out_of_range if nonexistent
		T& GetComponent(Entity e) {
			return components[entityToIndex.at(e)];
		}

		// Readonly get
		const T& GetComponentReadonly(Entity e) const {
			return components[entityToIndex.at(e)];
		}

		// Returns a readonly list of all the components of this type
		const std::vector<T>& GetAll() const {
			return components;
		}

		/// <summary>Returns a writable list of all the components of this type.
		/// <para>Do NOT rearrange this list. Use GetComponent() for safer access.</para>
		/// </summary>
		//std::vector<T>& GetAll() {
		//	return components;	// honestly this is kinda dangerous i might deprecate this unless the perf gain is much better than using GetComponent() in a loop
		//}

		// Returns a readonly list of all entities with this component
		const std::vector<Entity>& GetAllEntities() const { return entities; }
	};

}