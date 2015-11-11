#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_shader.h"

class Line
{
public:
	Line(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b, float a=1.0f);
	~Line();
	void load();
	void render(glm::mat4 &mat);
	void addPoints(float x, float y, float z);


private:
	void updateVBO(void* datas,unsigned int bytesSize, unsigned int offset);
	engine_shader m_shader;
	GLuint m_vbo; //VBO ID
	GLuint m_vao; //VAO iD
	unsigned int m_pointsBytesSize;
	unsigned int m_colorsBytesSize;
	//float m_point[6];
	std::vector<float> m_points;
	std::vector<float> m_colors;
	//float m_colors[8];
};

