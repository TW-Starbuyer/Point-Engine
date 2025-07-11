#pragma once
#include "defs.hpp"
#include "state.hpp"

#include "../utils/u_components.hpp"

class ScriptingEngine
{
	public:
		ScriptingEngine();
		void Update(World& world);
		void MapScripts();
		void RunScripts(World& world);

		void AddScript(Script script, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier);

	private:
		std::stack<Script> execution_stack;
		POINT::hashmap<EntityID, POINT::vector<Script>> scripts_map;
		
};