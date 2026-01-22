# Royal Jelly Physics

RoyalJellyPhysics is a C++ library for deterministic 2D physics, designed for developing fighting games.
It features deterministic physics calculations due to fixed-point math. The engine ensures a lockstep, so there are no constraints on the time fed into the engine.
The engine is written with minimal needs in mind and hence does not have features such as angular velocity. However, RoyalJellyPhysics is written to be easily extensible.

Note: Use seeded randoms to ensure clients are in sync.

## Roadmap

- Collision detection and resolution
- Force accumulation
- Clean serialization and encapsulation of world state

## Usage

```cpp
// Create a world and manipulate entities within it
RJPhysics::World world;

// Spawn an entity and attach components to it
RJPhysics::Entity e = world.CreateEntity();
world.positions.Add(e);
world.boxColliders.Add(e);
world.rigidbodies.Add(e);

// Step physics (planned rework), GetFrameTime() is NOT part of the library
world.IntegrateDynamicRigidbodies(fpm::q16_16(GetFrameTime()));

// Query, iteration
std::vector entitiesToRender = world.boxColliders.GetAllEntities();
		for (int i = 0; i < entitiesToRender.size(); i++) {
			// get relative position of box's pivot from camera
			RJPhysics::Vec2 relativeVector = world.positions.GetComponent(entitiesToRender[i]).position - cameraPos;

			// convert from world position to screen position
			RJPhysics::Vec2 posToRender = screenCenter + (relativeVector * fpm::q16_16(cameraZoom));
			
			RJPhysics::BoxCollider2D box = world.boxColliders.GetComponent(entitiesToRender[i]);

			// code to draw the boxes
		}
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
