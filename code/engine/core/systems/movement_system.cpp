#include "movement_system.hpp"

MovementSystem::MovementSystem() {}

void MovementSystem::Update(World& world)
{
	for (EntityID entity_id : world.element_registry.entities_w_movement)
	{
		velocity_component& velocity_cmpt = GetComponent<velocity_component>(world.component_store.velocities, entity_id);

		if (velocity_cmpt.has_changed == 1)
		{
			transform_component& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
			transform_cmpt.position += velocity_cmpt.velocity;
			velocity_cmpt.has_changed = 0;
		}
	}
}