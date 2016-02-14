#pragma once

//#include <vector>
#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine_shader.h"
#include "engine_texture.h"
#include "engine_window.h"
#include "MathUtil.h"

enum PhyxEnum {
	PHYX_INITMODE_UNIFORM
};

class ParticleSystem
{
public:
	ParticleSystem(float x, float y, float z, float w, float h, float depth,engine_window &window);
	~ParticleSystem();

	void load();
	
	void update();
	void physX(glm::mat4 &projection, glm::mat4 &modelview);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void texProcess(GLuint const& texToProcess, GLuint const& fbo, engine_shader const& shader, size_t texW, size_t texh);
	void fboDisplay();
	//bool copyTexture(GLuint src, GLuint des, );
	void initParticle(PhyxEnum mode, unsigned int sx, unsigned int sy, unsigned int sz);

	GLuint getFBOId() const;
	GLuint getFBOtexId() const;

	void dev_reloadPhyxShader();

	//void setR_T(GLuint t);
private:

	void init();
	void texProcessorInit();
	

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	GLuint m_uvao;//EMPTY vao but USEFULL

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
	engine_window &m_window;
	
	

	//
	GLenum m_drawBuffers[1];

	float m_bounds[8*3]; //The Bucket AND Container
	unsigned int m_edgesIndices[24];

	unsigned int m_boundsBytesSize;
	unsigned int m_indicesBytesSize;

	engine_shader m_shader;
	engine_shader m_shader_fbo;
	engine_shader m_phyX;
	engine_shader m_shaderInit;
	GLuint m_particles;//the particle
	GLuint m_grid;//2D texture for rigid object, bucket
	GLuint m_PreviousPos;
	GLuint m_LastPos;
	GLuint m_PreviousVel;
	GLuint m_LastVel;
	GLuint m_densityTexture;

};

