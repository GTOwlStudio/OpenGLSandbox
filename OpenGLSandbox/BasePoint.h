#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"

class BasePoint
{
public:
	BasePoint(engine_shader &shader);
	~BasePoint();
	void load();
	void render(glm::mat4 &matrix);

private:
	engine_shader &m_shader;
	GLuint m_vbo;
	GLuint m_vao;
	unsigned int m_coordsBytesSize;
	float m_coords[18];
	float m_colors[18];

};

