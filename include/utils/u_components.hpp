#pragma once

#include "../../include/headers/defs.hpp"
#include "../../include/headers/state.hpp"

template <typename CmptType, typename CmptContainer>
inline CmptType& GetComponent(CmptContainer& container, EntityID entity_id)
{
	int dense_index = container.sparse.at(entity_id);
	CmptType& cmpt = container.dense.at(dense_index);
	return cmpt;
}

template <typename CmptType, typename CmptContainer>
inline void AddComponent(World& world, CmptContainer& container, CmptType& cmpt, TAG cmpt_tag, EntityID entity_id)
{
	int dense_index = container.dense.size();
	container.dense.push_back(cmpt);
	container.sparse[entity_id] = dense_index;

	ComponentMask& cmpt_mask = world.entities_map.at(entity_id);
	cmpt_mask |= cmpt_tag;

}

 inline ComponentMask GetComponentMask(World& world, EntityID entity_id)
{
	 ComponentMask& cmpt_mask = world.entities_map.at(entity_id);
	 return cmpt_mask;
}




