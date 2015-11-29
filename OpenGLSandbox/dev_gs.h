#pragma once

#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_shader.h"
#include "engine_texture.h"

class dev_gs
{
public:
	//dev_gs(float x, float y, float w, float h, float depth, std::string vert, std::string frag, std::string geometry);
	//dev_gs(float x, float y, float w, float h, float depth, std::string vert, std::string frag, GLuint textureID);
	/*dev_gs(float vertices[18], std::string vert, std::string frag, std::string texture);
	dev_gs(float vertices[18], float texCoords[12], std::string vert, std::string frag, std::string texture);
	dev_gs(float vertices[18], float texCoords[12], std::string vert, std::string frag, GLuint textureID);*/
	dev_gs(float x, float y, float w, float h, float depth, std::string vert, std::string frag, std::string geometry);
	~dev_gs();
	void load();
	void render(glm::mat4 &projection, glm::mat4 &modelview);

private:
	GLuint m_vboID;
	GLuint m_vaoID;
	engine_shader m_shader;
	float m_vertices[18];
	int m_verticesBytesSize;

};

