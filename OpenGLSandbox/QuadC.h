#pragma once

#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_texture.h"
#include "engine_shader.h"
#include "gui_Object.h"

class QuadC : public gui_Object
{
public:
	QuadC(float x, float y, float w, float h, float depth, float r, float g, float b, float a);
	//QuadC(float x, float y, float w, float h, float depth, std::string vert, std::string frag, GLuint textureID);
	QuadC(float vertices[18], std::string vert, std::string frag, float colors[24]);
	~QuadC();
	void load();
	void update();
	void updateVBO(void* datas,unsigned int bytesSize, unsigned int offset);
	void setPosition(float x, float y);
	void setBounds(float w, float h);
	void render(glm::mat4 &projection, glm::mat4 &modelview);

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	

private:
	GLuint m_vboID;
	GLuint m_vaoID;
	//engine_texture m_texture;
	engine_shader m_shader;
	float m_vertices[18];
	float m_colors[24];
	int m_verticesBytesSize;
	int m_colorsBytesSize;
};

