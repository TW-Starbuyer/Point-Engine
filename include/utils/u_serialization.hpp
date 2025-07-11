#pragma once

#include "../../headers/defs.hpp"
#include "../../headers/state.hpp"



//template<class Archive>
//inline void serialize(Archive& archive, glm::vec2& vec)
//{
//	archive(cereal::make_nvp("x", vec.x),
//			cereal::make_nvp("y", vec.y)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, glm::vec3& vec)
//{
//	archive(cereal::make_nvp("x", vec.x),
//			cereal::make_nvp("y", vec.y),
//			cereal::make_nvp("z", vec.z)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, glm::vec4& vec)
//{
//	archive(cereal::make_nvp("x", vec.x),
//			cereal::make_nvp("y", vec.y),
//			cereal::make_nvp("z", vec.z),
//			cereal::make_nvp("w", vec.w)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, glm::mat4& mat)
//{
//	archive(cereal::make_nvp("m0", mat[0]),
//			cereal::make_nvp("m1", mat[1]),
//			cereal::make_nvp("m2", mat[2]),
//			cereal::make_nvp("m3", mat[3])
//	);
//}
//
//template<class Archive, typename ComponentType>
//inline void serialize(Archive& archive, Component<ComponentType>& cmpt)
//{
//	archive(cereal::make_nvp("sparse", cmpt.sparse),
//			cereal::make_nvp("dense", cmpt.dense),
//			cereal::make_nvp("reverse", cmpt.reverse)
//	);
//}
//
//
//template<class Archive>
//inline void serialize(Archive& archive, Vertex& vertex)
//{
//	archive(cereal::make_nvp("position", vertex.position),
//			cereal::make_nvp("color", vertex.color),
//			cereal::make_nvp("texture_coordinates", vertex.texture_coordinates)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, Texture& texture)
//{
//	archive(cereal::make_nvp("filename", texture.filename),
//			cereal::make_nvp("texture_id", texture.texture_id),
//			cereal::make_nvp("texture_repeat_scale", texture.texture_repeat_scale)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, Material& material)
//{
//	archive(cereal::make_nvp("shader_program_id", material.shader_program_id),
//			cereal::make_nvp("textures", material.textures)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, Mesh& mesh)
//{
//	archive(cereal::make_nvp("vertices", mesh.vertices),
//			cereal::make_nvp("indices", mesh.indices),
//			cereal::make_nvp("material", mesh.material)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, Model& model)
//{
//	archive(cereal::make_nvp("mesh_data", model.mesh_data),
//			cereal::make_nvp("model_matrix", model.model_matrix)
//	);
//}
//
//template <class Archive>
//inline void serialize(Archive& archive, model_component& cmpt)
//{
//	archive(cereal::make_nvp("model", cmpt.model),
//			cereal::make_nvp("has_changed", cmpt.has_changed)
//	);
//}
//
//template <class Archive>
//inline void serialize(Archive& archive, transform_component& cmpt)
//{
//	archive(cereal::make_nvp("position", cmpt.position),
//			cereal::make_nvp("rotation", cmpt.rotation),
//			cereal::make_nvp("scale", cmpt.scale),
//			cereal::make_nvp("has_changed", cmpt.has_changed)
//	);
//}
//
//template <class Archive>
//inline void serialize(Archive& archive, velocity_component& cmpt)
//{
//	archive(cereal::make_nvp("velocity", cmpt.velocity),
//			cereal::make_nvp("forward_speed", cmpt.forward_speed),
//			cereal::make_nvp("backwards_speed", cmpt.backwards_speed),
//			cereal::make_nvp("strafe_speed", cmpt.strafe_speed),
//			cereal::make_nvp("has_changed", cmpt.has_changed)
//	);
//}
//
//template <class Archive>
//inline void serialize(Archive& archive, camera_component& cmpt)
//{
//	archive(cereal::make_nvp("freelook", cmpt.freelook),
//			cereal::make_nvp("fov", cmpt.fov),
//			cereal::make_nvp("aspect_ratio", cmpt.aspect_ratio),
//			cereal::make_nvp("near_plane", cmpt.near_plane),
//			cereal::make_nvp("far_plane", cmpt.far_plane),
//			cereal::make_nvp("yaw", cmpt.yaw),
//			cereal::make_nvp("pitch", cmpt.pitch),
//			cereal::make_nvp("up", cmpt.up),
//			cereal::make_nvp("direction", cmpt.direction),
//			cereal::make_nvp("view_matrix", cmpt.view_matrix),
//			cereal::make_nvp("projection_matrix", cmpt.projection_matrix),
//			cereal::make_nvp("has_changed", cmpt.has_changed)
//	);
//}
//
//
//
//template <class Archive>
//inline void serialize(Archive& archive, World& world)
//{
//	archive(
//		cereal::make_nvp("entity_state", world.entity_state),
//		cereal::make_nvp("time_state", world.time_state),
//		cereal::make_nvp("models", world.models),
//		cereal::make_nvp("transforms", world.transforms),
//		cereal::make_nvp("velocities", world.velocities),
//		cereal::make_nvp("cameras", world.cameras)
//	);
//}
//
//
//template <class Archive>
//inline void serialize(Archive& archive, EntityState& entity_state )
//{
//	archive(
//		cereal::make_nvp("num_entities", entity_state.num_entities),
//		cereal::make_nvp("elements_map", entity_state.elements_map),
//		cereal::make_nvp("entities_w_movement", entity_state.entities_w_movement),
//		cereal::make_nvp("entities_w_camera", entity_state.entities_w_camera),
//		cereal::make_nvp("entities_w_model", entity_state.entities_w_model)
//	);
//}
//
//template<class Archive>
//inline void serialize(Archive& archive, TimeState& time_state)
//{
//	using rep = std::chrono::high_resolution_clock::duration::rep;
//
//	rep current_time = time_state.current_time.time_since_epoch().count();
//	rep last_time = time_state.last_time.time_since_epoch().count();
//
//	archive(
//		cereal::make_nvp("current_time", current_time),
//		cereal::make_nvp("last_time", last_time),
//		cereal::make_nvp("delta_time", time_state.delta_time)
//	);
//
//	if (Archive::is_loading::value)
//	{
//		time_state.current_time = std::chrono::high_resolution_clock::time_point(
//			std::chrono::high_resolution_clock::duration(current_time)
//		);
//
//		time_state.last_time = std::chrono::high_resolution_clock::time_point(
//			std::chrono::high_resolution_clock::duration(last_time)
//		);
//	}
//}

