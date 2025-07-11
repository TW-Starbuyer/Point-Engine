#pragma once

#include "../../include/headers/defs.hpp"
#include "u_components.hpp"

inline bool HasCmptTAG(ComponentMask component_mask, TAG cmpt_tag)
{
	return (component_mask & cmpt_tag) == cmpt_tag;
}

inline bool HasSysTAG(ComponentMask component_mask, TAG sys_tag)
{
	return (component_mask & sys_tag) == sys_tag;
}

inline void AddTAGToEntity(World& world, TAG tag, EntityID entity_id)
{
	ComponentMask& entity_mask = world.entities_map.at(entity_id);
	entity_mask |= tag;
}

inline void AddTAGToComponentMask(ComponentMask& component_mask, TAG tag)
{
	component_mask |= tag;
}

inline std::string GetEntityArchetype(World& world, EntityID entity_id)
{
	std::string archetype;
	ComponentMask component_mask = GetComponentMask(world, entity_id);

	if (component_mask == TAG_ARCH_PLAYER)
	{
		archetype = "PLAYER";
		return archetype;
	}

	if (component_mask == TAG_ARCH_CAMERA)
	{
		archetype = "CAMERA";
		return archetype;
	}

	if (component_mask == TAG_ARCH_GEOMETRY)
	{
		archetype = "GEOMETRY";
		return archetype;
	}

	else
	{
		archetype = "CUSTOM";
		return archetype;
	}
}

//// Archetype TAGs
//constexpr TAG TAG_ARCH_PLAYER =		TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY | TAG_CMPT_MODEL | TAG_CMPT_CAMERA;
//constexpr TAG TAG_ARCH_CAMERA =		TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY |                  TAG_CMPT_CAMERA;
//constexpr TAG TAG_ARCH_GEOMETRY 
