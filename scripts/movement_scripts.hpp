#pragma once

#include "defs.hpp"
#include "state.hpp"


#include "../utils/u_components.hpp"

void RotateEntityX(World& world, EntityID entity_id,  float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	transform_cmpt.rotation.x += modifier;
	transform_cmpt.has_changed = 1;
}
Script SCRIPT_rotate_entity_x(RotateEntityX);

void RotateEntityY(World& world, EntityID entity_id,  float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	transform_cmpt.rotation.y += modifier;
	transform_cmpt.has_changed = 1;
}
Script SCRIPT_rotate_entity_y(RotateEntityY);

void RotateEntityZ(World& world, EntityID entity_id,  float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	transform_cmpt.rotation.z += modifier;
	transform_cmpt.has_changed = 1;
}
Script SCRIPT_rotate_entity_z(RotateEntityZ);


void ScaleUpEntity(World& world, EntityID entity_id,  float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	transform_cmpt.scale += glm::vec3(modifier, modifier, modifier);
	transform_cmpt.has_changed = 1;
}
Script SCRIPT_scale_up_entity(ScaleUpEntity);



void StrafeElementX(World& world, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	auto& velocity_cmpt = GetComponent<velocity_component>(world.component_store.velocities, entity_id);

	if (velocity_cmpt.velocity.x == 0.0f)
	{
		velocity_cmpt.velocity.x = modifier;
	}

	if (transform_cmpt.position.x >= target_max)
	{
		velocity_cmpt.velocity.x = -modifier;
	}

	else if (transform_cmpt.position.x <= target_min)
	{
		velocity_cmpt.velocity.x = modifier;
		
	}
	
	transform_cmpt.has_changed = 1;
	velocity_cmpt.has_changed = 1;
}
Script SCRIPT_strafe_element_x(StrafeElementX);

void StrafeElementY(World& world, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	auto& velocity_cmpt = GetComponent<velocity_component>(world.component_store.velocities, entity_id);

	if (velocity_cmpt.velocity.y == 0.0f)
	{
		velocity_cmpt.velocity.y = modifier;
	}

	if (transform_cmpt.position.y >= target_max)
	{
		velocity_cmpt.velocity.y = -modifier;
	}

	else if (transform_cmpt.position.y <= target_min)
	{
		velocity_cmpt.velocity.y = modifier;
		
	}
	
	transform_cmpt.has_changed = 1;
	velocity_cmpt.has_changed = 1;
}
Script SCRIPT_strafe_element_y(StrafeElementY);

void StrafeElementZ(World& world, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier)
{
	auto& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
	auto& velocity_cmpt = GetComponent<velocity_component>(world.component_store.velocities, entity_id);

	if (velocity_cmpt.velocity.z == 0.0f)
	{
		velocity_cmpt.velocity.z = modifier;
	}

	if (transform_cmpt.position.z >= target_max)
	{
		velocity_cmpt.velocity.z = -modifier;
	}

	else if (transform_cmpt.position.z <= target_min)
	{
		velocity_cmpt.velocity.z = modifier;
		
	}
	
	transform_cmpt.has_changed = 1;
	velocity_cmpt.has_changed = 1;
}
Script SCRIPT_strafe_element_z(StrafeElementZ);

