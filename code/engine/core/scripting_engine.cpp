#include "scripting_engine.hpp"

ScriptingEngine::ScriptingEngine()
{

};

void ScriptingEngine::Update(World& world)
{
	MapScripts();
	RunScripts(world);
}

void ScriptingEngine::MapScripts()
{
	for (auto& key_pair : scripts_map)
	{
		EntityID entity_id = key_pair.first;

		for (int i = 0; i < key_pair.second.size(); i++)
		{
			Script& script = key_pair.second.at(i);
			script.target_entity_id = entity_id;
			execution_stack.push(script);
		}
	}
}

void ScriptingEngine::RunScripts(World& world)
{
	while (!execution_stack.empty())
	{
		Script& script = execution_stack.top();
		script.run(world);
		execution_stack.pop();
	}
}

void ScriptingEngine::AddScript(Script script, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier)
{
	script.multiplier = multiplier;
	script.modifier = modifier;
	script.target_min = target_min;
	script.target_max = target_max;
	scripts_map[entity_id].push_back(script);
}
