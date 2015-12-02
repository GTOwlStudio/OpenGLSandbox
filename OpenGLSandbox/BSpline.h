#pragma once


#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_shader.h"

class BSpline
{
public:
	BSpline(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b, float a=1.0f);
	~BSpline();
	void load();
	void render(glm::mat4 &mat);
	void addControlPoint(float x, float y, float z);
	void generateSpline(float step);

protected:
	float bezierCubic(float v0, float v1, float v2, float v3, float t); //data an array of 4*3 float

private:
	void updateVBO(void* datas,unsigned int bytesSize, unsigned int offset);
	void dev_generateSplineUpdate(int bytesSize);
	engine_shader m_shader; //The display shader
	GLuint m_vbo; //VBO ID of control vertices
	GLuint m_vbo_spline; //VBO ID of points
	GLuint m_vao; //VAO iD
	unsigned int m_controlBytesSize;
	unsigned int m_pointsBytesSize;
	unsigned int m_colorsBytesSize;
	//float m_point[6];
	std::vector<float> m_control; //Control Points
	std::vector<float> m_points;
	std::vector<float> m_colors;
};

