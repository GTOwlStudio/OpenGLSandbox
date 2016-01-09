#pragma once

//#include <vector>
#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"
#include "engine_texture.h"

class ParticleSystem
{
public:
	ParticleSystem(float x, float y, float z, float w, float h, float depth);
	~ParticleSystem();

	void load();
	
	void update();
	void physX(glm::mat4 &projection, glm::mat4 &modelview);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void texProcess();
	void fboDisplay();
	//void setR_T(GLuint t);
private:

	void init();
	void texProcessorInit();
	

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	GLuint m_fbo;
//	GLuint m_renderBuffer;
	
	//TextureProcessor
	//GLuint tp_rt;
	unsigned char p[3];
	GLuint tp_vao;
	GLuint tp_vbo;
	GLuint tp_ibo;
	float tp_vertices[8];
	float tp_texCoords[8];
	unsigned int tp_indices[6];
	unsigned int tp_texCoordsBytesSize;
	unsigned int tp_verticesBytesSize;
	unsigned int tp_indicesBytesSize;
	

	//
	GLenum m_drawBuffers[1];

	float m_bounds[8*3]; //The Bucket AND Container
	unsigned int m_edgesIndices[24];

	unsigned int m_boundsBytesSize;
	unsigned int m_indicesBytesSize;

	engine_shader m_shader;
	engine_shader m_shader_fbo;
	engine_shader m_phyX;
	GLuint m_particles;//the particle
	GLuint m_grid;//2D texture for rigid object, bucket
	GLuint m_PreviousPos;
	GLuint m_LastPos;
	GLuint m_PreviousVel;
	GLuint m_LastVel;
	GLuint m_densityTexture;

};

