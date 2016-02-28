#pragma once
#include <string>
#include "engine_shader.h"
#include "RessourcesManager.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class EzyTex
{
public:
	EzyTex(GLuint id);
	~EzyTex();
	void load();
	void render(glm::mat4 &matrix);
	

private:
	GLuint m_tid;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	engine_shader m_shader;

	float m_coords[8];
	float m_texCoords[8];
	unsigned int m_indices[6];

	unsigned int m_coordsBytesSize;
	unsigned int m_texCoordsBytesSize;
	unsigned int m_indicesBytesSize;

};

