#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"
#include "../utils/u_components.hpp"

class CameraSystem
{
	public:
		CameraSystem();
		void Update(World& world, RenderState& render_state);
		void SetActiveCamera(World& world, RenderState& render_state, EntityID entity_id);
};
