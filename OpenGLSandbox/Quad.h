#pragma once

#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_texture.h"
#include "engine_shader.h"


class Quad
{
public:
	Quad(float x, float y, float w, float h, float depth, std::string vert, std::string frag, std::string texture);
	Quad(float x, float y, float w, float h, float depth, std::string vert, std::string frag, GLuint textureID);
	Quad(float vertices[18], std::string vert, std::string frag, std::string texture);
	~Quad();
	void load();
	void render(glm::mat4 &projection, glm::mat4 &modelview);

private:
	GLuint m_vboID;
	GLuint m_vaoID;
	engine_texture m_texture;
	engine_shader m_shader;
	float m_vertices[18];
	float m_texCoords[12];
	int m_verticesBytesSize;
	int m_texCoordsBytesSize;
};

