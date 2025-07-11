#pragma once
#include "components.hpp"
#include "defs.hpp"


struct Framebuffer
{
	GLuint FBO;
	GLuint RBO;
	GLuint texture_id;
};

struct ElementRegistry
{
	POINT::vector<EntityID> entities_w_movement;
	POINT::vector<EntityID> entities_w_camera;
	POINT::vector<EntityID> entities_w_model;
	POINT::vector<EntityID> entities_w_script;
};

template <class ComponentType>
class ComponentSets
{
	public:
		POINT::vector<int> sparse;
		POINT::vector<ComponentType> dense;
};

struct TimeState
{
	POINT::hashmap<std::string, int> counters;
	std::chrono::high_resolution_clock::time_point current_time;
	std::chrono::high_resolution_clock::time_point last_time;
	float delta_time;
};

struct ComponentStore
{
	ComponentSets<model_component> models;
	ComponentSets<transform_component> transforms;
	ComponentSets<velocity_component> velocities;
	ComponentSets<camera_component> cameras;
};


struct RenderState
{
	Framebuffer active_framebuffer;
	bool scene_window_active = false;
	int active_camera_entity_id = -1;
	GLint model_matrix_location;
	GLint projection_location;
	GLint view_matrix_location;
	GLint texture_repeat_scale_location;
};


struct World
{
	ComponentStore component_store;
	POINT::hashmap<EntityID, ComponentMask> entities_map;
	ElementRegistry element_registry;
	TimeState time_state;
	RenderState render_state;
};

class Script
{
	public:
		std::function<void(World& world, EntityID entity_id,  float target_min, float target_max, float multiplier, float modifier)> src;

		EntityID target_entity_id = -1;
		unsigned int is_active = 1;

		float multiplier = 1.0;
		float modifier = 0.0;
		float target_min = 0.0;
		float target_max = 0.0;

		Script(std::function<void(World& world, EntityID entity_id, float target_min, float target_max, float multiplier, float modifier)> func) : src(func) {}

		Script() = default;

		void run(World& world)
		{
			if (is_active && src && (target_entity_id >= 0))
			{
				src(world, target_entity_id, target_min, target_max, multiplier, modifier);
			}
		}
};
