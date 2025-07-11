#pragma once

#include "defs.hpp"

struct Component
{
	unsigned int has_changed = 1;

};

struct transform_component : public Component
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(90.0f, 0.0f, 0.0f);	
	glm::vec3 scale = glm::vec3(100.0f, 1.0f, 100.0f);
};

struct velocity_component : public Component
{
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	float forward_speed = 30.0f;
	float backwards_speed = 30.0f;
	float strafe_speed = 30.0f;
};


struct model_component : public Component
{
	Model model;
};

struct camera_component : public Component
{
	float freelook;
	float fov = 80.f;
	float aspect_ratio = 1.6f; // Multiplying is good enough, no divison needed.
	float near_plane = 0.1f;
	float far_plane = 3000.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 direction = glm::vec3(0.0f, 1.0f, 0.0f);
	// Initialize to identity matrices.
	glm::mat4 view_matrix = glm::mat4(1.0);
	glm::mat4 projection_matrix = glm::mat4(1.0);
};





