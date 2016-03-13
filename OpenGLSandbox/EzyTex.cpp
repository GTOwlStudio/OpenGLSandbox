#include "EzyTex.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

EzyTex::EzyTex(GLuint id) : m_tid(id), m_vbo(0), m_vao(0), m_ibo(0), m_coordsBytesSize(sizeof(float) * 8),
m_texCoordsBytesSize(sizeof(float) * 8), m_indicesBytesSize(sizeof(unsigned int) * 6), m_shaderId(RessourcesManager::getShaderId("texture2d"))//, m_shader("shaders/texture2d.vert", "shaders/texture2d.frag")
{
	float tmpCoords[8] = { -1.0f, -1.0f,		-1.0f,1.0f,		1.0f,1.0f,	1.0, -1.0 };
	//float tmpCoords[8] = { 0.0f, -0.0f,		0.0f,1.0f,		1.0f,1.0f,	1.0, 0.0 };
	float tmpTex[8] = { 0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f, 1.0f,0.0f };
	unsigned int tmpIndices[6] = {0,1,2,0,2,3};
	for (unsigned int i = 0; i < 8;i++) {
		m_coords[i] = tmpCoords[i];
		m_texCoords[i] = tmpTex[i];
	}
	for (unsigned int i = 0; i < 6;i++) {
		m_indices[i] = tmpIndices[i];
	}
}

EzyTex::EzyTex(GLuint id, std::string ssv, std::string ssf) : m_tid(id), m_vbo(0), m_vao(0), m_ibo(0), m_coordsBytesSize(sizeof(float) * 8),
m_texCoordsBytesSize(sizeof(float) * 8), m_indicesBytesSize(sizeof(unsigned int) * 6), m_shader(ssv, ssf)
{
	float tmpCoords[8] = { -1.0f, -1.0f,		-1.0f,1.0f,		1.0f,1.0f,	1.0, -1.0 };
	//float tmpCoords[8] = { 0.0f, -0.0f,		0.0f,1.0f,		1.0f,1.0f,	1.0, 0.0 };
	float tmpTex[8] = { 0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f, 1.0f,0.0f };
	unsigned int tmpIndices[6] = { 0,1,2,0,2,3 };
	for (unsigned int i = 0; i < 8; i++) {
		m_coords[i] = tmpCoords[i];
		m_texCoords[i] = tmpTex[i];
	}
	for (unsigned int i = 0; i < 6; i++) {
		m_indices[i] = tmpIndices[i];
	}
}

EzyTex::~EzyTex()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

void EzyTex::load()
{

	if (glIsVertexArray(m_vao)) { glDeleteVertexArrays(1,&m_vao); }
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

		if (glIsBuffer(m_ibo)) { glDeleteBuffers(1, &m_ibo); }
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesBytesSize, m_indices, GL_STATIC_DRAW);

		if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize + m_texCoordsBytesSize, m_coords, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_texCoordsBytesSize,m_texCoords);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_coordsBytesSize));
		glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	//m_shader.load();

}

void EzyTex::render(glm::mat4 & matrix)
{
	
	glDisable(GL_DEPTH_TEST);
	//glUseProgram(m_shader.getProgramID());
	glUseProgram(m_shaderId);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderId, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));

		glBindVertexArray(m_vao);
		glBindTexture(GL_TEXTURE_2D, m_tid);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		glBindTexture(GL_TEXTURE_2D,0);
		glBindVertexArray(0);

	glUseProgram(0);
	glEnable(GL_DEPTH_TEST);
}




