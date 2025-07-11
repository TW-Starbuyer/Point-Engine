
#include "camera_system.hpp"

CameraSystem::CameraSystem() {}

void CameraSystem::Update(World& world, RenderState& render_state)
{
	for (EntityID entity_id : world.element_registry.entities_w_camera)
	{
		transform_component& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);
		camera_component& camera_cmpt = GetComponent<camera_component>(world.component_store.cameras, entity_id);

		camera_cmpt.view_matrix = glm::lookAt(transform_cmpt.position, transform_cmpt.position + camera_cmpt.direction, camera_cmpt.up);
		camera_cmpt.projection_matrix = glm::perspective(glm::radians(camera_cmpt.fov), camera_cmpt.aspect_ratio, camera_cmpt.near_plane, camera_cmpt.far_plane);
	}
};

void CameraSystem::SetActiveCamera(World& world, RenderState& render_state, EntityID entity_id)
{
	render_state.active_camera_entity_id = entity_id;
}


