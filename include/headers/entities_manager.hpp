#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"
#include "resource_manager.hpp"

#include "../utils/u_tags.hpp"
#include "../utils/u_models.hpp"
#include "../utils/u_components.hpp"

#include <unordered_set>


class EntitiesManager
{
public:
		EntitiesManager();
		void Update(World& world);
		EntityID CreateElement(World& world);
		void SortElementsByTAG(World& world);

	private:
		int num_of_entities = 0;
		std::unordered_set<EntityID> entities_ids_set;
};

