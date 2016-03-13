#pragma once
#include "glheader.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"

class Mesh
{
public:
	Mesh(std::string filename);
	~Mesh();
	void update();
	void load();
	void render(glm::mat4 &matrix);
	void render(glm::mat4 &matrix, glm::mat4 &world); //For Diffuse Lighting

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<unsigned int> m_indices;
	void loadFromFile(std::string filename);
	void computeNormals();

	//DEV
	unsigned int m_verticesBytesSize;
	unsigned int m_normalsBytesSize;
	unsigned int m_indicesBytesSize;
	engine_shader m_shader;
	GLuint m_vao;
	GLuint m_ibo;
	GLuint m_vbo;
	

};

