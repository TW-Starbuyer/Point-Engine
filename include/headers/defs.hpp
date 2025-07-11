#pragma once
#include "stl_headers.hpp"
#include "third_party.hpp"
#include "engine_state.hpp"


namespace POINT
{
	template<typename T>
	using vector = std::vector<T>;

	template<typename T1, typename T2>
	using hashmap = std::unordered_map<T1, T2>;
}

// ID type aliases
using EntityID = int;
using ComponentID = int; 
using MeshID = int;
using ModelID = int;
using TextureID = int;
using ShaderID = int;
using MaterialID = int;
using TransformID = int;

using TexturesReq = POINT::hashmap<std::string, float>;

using ComponentMask = uint64_t;
using TAG = uint64_t;

const int INVALID_ELEMENT_ID = -1;
const int EMPTY_COMPONENT_MASK = 0;


// Component TAGs
constexpr TAG TAG_CMPT_TRANSFORM =		1ULL << 0;
constexpr TAG TAG_CMPT_VELOCITY =		1ULL << 1;
constexpr TAG TAG_CMPT_MODEL =			1ULL << 2;
constexpr TAG TAG_CMPT_CAMERA =			1ULL << 3;
constexpr TAG TAG_CMPT_SCRIPT =			1ULL << 4;

// System TAGs
constexpr TAG TAG_SYS_MOVEMENT =	TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY;
constexpr TAG TAG_SYS_CAMERA =		TAG_CMPT_CAMERA;
constexpr TAG TAG_SYS_MODEL =		TAG_CMPT_TRANSFORM | TAG_CMPT_MODEL;
constexpr TAG TAG_SYS_SCRIPTING =	TAG_CMPT_SCRIPT;

// Archetype TAGs
constexpr TAG TAG_ARCH_PLAYER =		TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY | TAG_CMPT_MODEL | TAG_CMPT_CAMERA;
constexpr TAG TAG_ARCH_CAMERA =		TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY |                  TAG_CMPT_CAMERA;
constexpr TAG TAG_ARCH_GEOMETRY =	TAG_CMPT_TRANSFORM | TAG_CMPT_VELOCITY | TAG_CMPT_MODEL;


// Custom enum types
enum ComponentType
{
	CMPT_TRANSFORM,
	CMPT_VELOCITY,
	CMPT_MODEL,
	CMPT_CAMERA,
	CMPT_SCRIPT
};


enum EntityType
{
	ENT_PLAYER,
	ENT_CAMERA,
	ENT_GEOMETRY,
};

enum MaterialType
{
	MTL_BRICK,
	MTL_CONCRETE,
};

enum CameraType
{
	CAM_LOCKED_Y,
	CAM_FREE,
};

enum GeometryType
{
	GEO_CUBE,
	GEO_TEAPOT,
	GEO_SPONZA
};


enum ShaderType
{
	SHDR_VERTEX,
	SHDR_FRAGMENT
};


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 texture_coordinates;
};

struct Texture
{
	std::string filename;
	TextureID texture_id;
	float texture_repeat_scale = 1.0f;
};

struct Material
{
	ShaderID shader_program_id = -1;
	POINT::vector<Texture> textures;
};

struct Mesh
{
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint IBO = 0;
	POINT::vector<Vertex> vertices;
	POINT::vector<GLuint> indices;
	Material material;
};

struct Model
{
	POINT::vector<Mesh> mesh_data;
	glm::mat4 model_matrix = glm::mat4();
};

struct Window
{
	std::string window_title;
	SDL_Window* SDLwindow;
	SDL_GLContext GLContext;
};
















