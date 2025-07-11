#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"


#include "../utils/u_components.hpp"

class MovementSystem
{
	public:
		MovementSystem();
		void Update(World& world);
};