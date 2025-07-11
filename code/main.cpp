#include "point.hpp"

int main()
{
	// Create instance.
	Point point;
	
	// Initial engine configurations.
	point.core.configs.gl_depth_test = true;

	// Call update configs when done.
	point.core.UpdateConfigs();

	// Declare what textures and materials you'd like retrieved at the start of runtime.
	Texture tx_grass = point.intr.POINT_resources.GetTexture("grass-texture.jpg");
	Texture tx_stone = point.intr.POINT_resources.GetTexture("stone-texture.jpg");

	// Arg1: vertex shader name, Arg2: fragment shader name, Arg3: texture, Arg4: scale.
	Material mt_grass = point.intr.POINT_materials.CreateMaterial("hello_shader.vert", "hello_shader.frag", tx_grass, 750.0f);
	Material mt_stone = point.intr.POINT_materials.CreateMaterial("hello_shader.vert", "hello_shader.frag", tx_stone, 1.0f);

	// Create geometry and apply materials, Arg1: model file, Arg2: position, Arg3: rotation, Arg4: scale.
	EntityID ground = point.intr.POINT_world.CreateGeometry("primitives/cube.glb", glm::vec3(0.0f, 0.0f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1000.0f, 1.0f, 1000.0f));
	EntityID teapot = point.intr.POINT_world.CreateGeometry("objects/the_utah_teapot.glb", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));

	// Call this function to then apply the material to every mesh in the model for an entity.
	point.core.materials_system.ApplyMaterialToEachMeshInModel(point.core.world, mt_grass, ground);
	point.core.materials_system.ApplyMaterialToEachMeshInModel(point.core.world, mt_stone, teapot);

	// Declare cameras here, Arg1: Select camera movement restriction option, Arg2: position, Arg3: rotation.
	EntityID editor_camera = point.intr.POINT_world.CreateCamera(CAM_FREE, glm::vec3(0.0f, -20.0f, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	EntityID player_camera = point.intr.POINT_world.CreateCamera(CAM_LOCKED_Y, glm::vec3(0.0f, -20.0f, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// Make sure to set the first active camera. This can be switched with the runtime editor.
	point.core.ECS_camera_system.SetActiveCamera(point.core.world, point.core.world.render_state, editor_camera);
	
	// Run instance.
	point.Run();
}