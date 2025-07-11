#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



#include "../../include/headers/defs.hpp"
#include "../../include/third_party/tiny_obj_loader/tiny_obj_loader.h"

inline void initialize_mesh(Mesh& mesh)
{
	// Generate and bind VAO.
	glGenVertexArrays(1, &mesh.VAO);
	glBindVertexArray(mesh.VAO);

	// Generate and bind VBO.
	glGenBuffers(1, &mesh.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

	// Generate and bind IBO.
	glGenBuffers(1, &mesh.IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.IBO);

	// Create GL array and element buffers.
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), mesh.indices.data(), GL_STATIC_DRAW);

	// Vertex positions.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	//Vertex colors.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinates));
	
	// Unbind buffer and disable when done.
	glBindVertexArray(0);

    //std::cout << "Model initialized" << std::endl;
}

inline void initialize_model(Model& model)
{
    for (auto& mesh : model.mesh_data)
    {
        initialize_mesh(mesh);
    }
}
