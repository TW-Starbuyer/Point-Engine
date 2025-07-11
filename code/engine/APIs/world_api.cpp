#include "world_api.hpp"


WorldAPI::WorldAPI(Core& core) : core(core){}

EntityID WorldAPI::CreateCamera(CameraType camera_type, glm::vec3 init_position, glm::vec3 init_rotation)
{
	auto entity_id = core.entities_manager.CreateElement(core.world);

	camera_component camera_cmpt;
	velocity_component velocity_cmpt;
	transform_component transform_cmpt;

	switch (camera_type)
	{
		case CAM_FREE:
		{
			camera_cmpt.freelook = true;
			break;
		}

		case CAM_LOCKED_Y:
		{
			camera_cmpt.freelook = false;
			break;
		}

		default:
			break;
	}


	transform_cmpt.position = init_position;
	transform_cmpt.rotation += init_rotation;

	AddComponent(core.world, core.world.component_store.cameras, camera_cmpt, TAG_CMPT_CAMERA, entity_id);
	AddComponent(core.world, core.world.component_store.velocities, velocity_cmpt, TAG_CMPT_VELOCITY, entity_id);
	AddComponent(core.world, core.world.component_store.transforms, transform_cmpt, TAG_CMPT_TRANSFORM, entity_id);
	

	AddTAGToEntity(core.world, TAG_ARCH_CAMERA, entity_id);	

	std::cout << "Camera element created!" << std::endl;

	return entity_id;
}

EntityID WorldAPI::CreateGeometry(std::string model_filename, glm::vec3 init_position, glm::vec3 init_rotation, glm::vec3 init_scale)
{
	auto entity_id = core.entities_manager.CreateElement(core.world);

	model_component model_cmpt;
	velocity_component velocity_cmpt;
	transform_component transform_cmpt;

	model_cmpt.model = core.resource_manager.GetModel(model_filename);
	initialize_model(model_cmpt.model);
	
	transform_cmpt.position = init_position;
	transform_cmpt.rotation += init_rotation;
	transform_cmpt.scale = init_scale;


	AddComponent(core.world, core.world.component_store.models, model_cmpt, TAG_CMPT_MODEL, entity_id);
	AddComponent(core.world, core.world.component_store.velocities, velocity_cmpt, TAG_CMPT_VELOCITY, entity_id);
	AddComponent(core.world, core.world.component_store.transforms, transform_cmpt, TAG_CMPT_TRANSFORM, entity_id);

	core.world.entities_map[entity_id] |= TAG_ARCH_GEOMETRY;

	AddTAGToEntity(core.world, TAG_ARCH_GEOMETRY, entity_id);

	
	std::cout << "Geometry element created!" << std::endl;

	return entity_id;	
}

