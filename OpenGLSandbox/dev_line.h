#pragma once

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"

class dev_line
{
public:
	dev_line(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2);
	~dev_line();
	void load();
	void render(glm::mat4 &projection, glm::mat4 &modelview);

private:
	engine_shader m_shader;
	GLuint m_vao;
	GLuint m_ibo;
	GLuint m_vbo;

	float m_coords[9];
	unsigned int m_indices[4];

	unsigned int m_coordsBytesSize;
	unsigned int m_indicesBytesSize;

};

