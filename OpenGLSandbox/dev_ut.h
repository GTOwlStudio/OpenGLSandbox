#pragma once
//Class for easier TEXTURE UNSIGNED INT MANAGMENT
//Easy "FBO and Texture" managment
//For The texProcess() func in the ParticleSystem class
#include "engine_shader.h"
class dev_ut
{
public:
	dev_ut();
	void load();
	GLuint getFBOId() const;
	GLuint getTexId() const;
	engine_shader getShader() const;
	~dev_ut();

private:
	GLuint m_fbo;
	GLuint m_t;
	engine_shader m_shader;
};

