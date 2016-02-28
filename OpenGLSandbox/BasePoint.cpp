#include "BasePoint.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

BasePoint::BasePoint(engine_shader &shader) : m_coordsBytesSize(sizeof(float) * 18), m_shader(shader)
{
	float tmpCoords[18] = {.0f,.0f,.0f,	1.0f,.0f,.0f,	.0f,.0f,.0f, .0f,1.0f,.0f,		.0f,.0f,.0f,	.0f,.0f,1.0f};
	for(int i = 0; i < 18;i++) {
		m_coords[i] = tmpCoords[i];
	}
	float tmpColors[18] = {1.0f,.0f,.0f,	 1.0f,.0f,.0f,		0.0f,1.0f,0.0f,	0.0f,1.0f,0.0f,		0.0f,0.0f,1.0f, 0.0f,0.0f,1.0f };
	for (int i = 0; i < 18;i++) {
		m_colors[i] = tmpColors[i];
	}
}


BasePoint::~BasePoint()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void BasePoint::load()
{
	if (glIsVertexArray(m_vao)) {glDeleteVertexArrays(1, &m_vao);}
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }
	glGenBuffers(1, &m_vbo);
	printf("Bp vbo = %i\n", m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize*2, m_coords, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_coordsBytesSize, m_colors);

	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,0,0) ;
	glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(m_coordsBytesSize));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BasePoint::render(glm::mat4 &matrix) {
	glUseProgram(m_shader.getProgramID());
		
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(matrix));

	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);

	glUseProgram(0);
}


