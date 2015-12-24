#pragma once

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"

class dev_Quad
{
public:
	dev_Quad(float x, float y, float w, float h, float depth, float r, float g, float b, float a);
	~dev_Quad();
	void load();
	void render(glm::mat4 &projection, glm::mat4 &modelview);

private:
	GLuint m_vaoId;
	GLuint m_vboId;
	GLuint m_iboId;
	engine_shader m_shader;
	float m_vertices[12];
	float m_colors[12];
	unsigned int m_index[6];
	unsigned int m_verticesBytesSize;
	unsigned int m_colorsBytesSize;
	unsigned int m_indexBytesSize;

};

