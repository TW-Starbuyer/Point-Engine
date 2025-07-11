#include "entities_manager.hpp"


EntitiesManager::EntitiesManager()
{
	for (int i = 0; i < 1000; i++)
	{
		entities_ids_set.insert(i);
	}
}

void EntitiesManager::Update(World& world)
{
	SortElementsByTAG(world);
}

EntityID EntitiesManager::CreateElement(World& world)
{
	EntityID entity_id = INVALID_ELEMENT_ID;

	if (!(entities_ids_set.empty()))
	{
		entity_id = *entities_ids_set.begin();
		entities_ids_set.erase(entities_ids_set.begin());

		world.entities_map[entity_id] = EMPTY_COMPONENT_MASK;
	}
	else
	{
		std::cerr << "Maxmimum number of entities assigned" << std::endl;
	}

	num_of_entities = entities_ids_set.size();
	
	return entity_id;
}

void EntitiesManager::SortElementsByTAG(World& world)
{
	world.element_registry.entities_w_movement.clear();
	world.element_registry.entities_w_camera.clear();
	world.element_registry.entities_w_model.clear();

	for (const auto& [entity_id, component_mask] : world.entities_map)
	{
		if (HasSysTAG(component_mask, TAG_SYS_MOVEMENT))
		{
			world.element_registry.entities_w_movement.push_back(entity_id);
		}

		if (HasSysTAG(component_mask, TAG_SYS_CAMERA))
		{
			world.element_registry.entities_w_camera.push_back(entity_id);
		}

		if (HasSysTAG(component_mask, TAG_SYS_MODEL))
		{
			world.element_registry.entities_w_model.push_back(entity_id);
		}

		if (HasSysTAG(component_mask, TAG_SYS_SCRIPTING))
		{
			world.element_registry.entities_w_script.push_back(entity_id);
		}
	}
}


