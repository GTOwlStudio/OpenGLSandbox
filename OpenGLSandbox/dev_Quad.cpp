#include "dev_Quad.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

dev_Quad::dev_Quad(float x, float y, float w, float h, float depth, float r, float g, float b, float a) : m_verticesBytesSize(sizeof(float) * 12), m_colorsBytesSize(sizeof(float) * 12), m_indexBytesSize(sizeof(unsigned int)*6),
m_vaoId(0), m_vboId(0), m_iboId(0), m_shader("shaders/dev_quad.vert", "shaders/dev_quad.frag")
{
	
	float tmpV[12] = {x,y+h,depth,	x+w,y+w,depth, x+w,y,depth, x,y,depth};
	for (int i = 0; i < 12;i++) {
		m_vertices[i] = tmpV[i];
	}

	//float tmpC[16] = {r,g,b,a,	r,g,b,a,	r,g,b,a,	r,g,b,a};
	//float tmpC[12] = { r,g,b,	r,g,b,	r,g,b,	r,g,b };
	float tmpC[12] = { 1.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,	1.0f,0.0f,1.0f };
	for (int i = 0; i < 16; i++) {
		m_colors[i] = tmpC[i];
	}
	float tmpI[6] = {0,1,3,	1, 2,3};
	for (int i = 0; i < 6;i++) {
		m_index[i]=tmpI[i];
	}

}


dev_Quad::~dev_Quad()
{
	glDeleteVertexArrays(1, &m_vaoId);
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
}


void dev_Quad::load() {
	m_shader.load();

	if (glIsVertexArray(m_vaoId)) {glDeleteVertexArrays(1, &m_vaoId);}

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);


		if (glIsBuffer(m_iboId)) {glDeleteBuffers(1, &m_iboId);}

		glGenBuffers(1, &m_iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexBytesSize, m_index, GL_STATIC_DRAW);
		
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);

		if (glIsBuffer(m_vboId)) {glDeleteBuffers(1, &m_vboId);	}
		
		glGenBuffers(1, &m_vboId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, m_verticesBytesSize+m_colorsBytesSize, m_vertices,GL_STATIC_DRAW);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesBytesSize, m_vertices);
		glBufferSubData(GL_ARRAY_BUFFER, m_verticesBytesSize, m_colorsBytesSize, m_colors);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 0,BUFFER_OFFSET(m_verticesBytesSize));
		glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	printf("dev_Quad vboID=%i\n", m_vboId);
}

void dev_Quad::render(glm::mat4 &projection, glm::mat4 &modelview) {

	glUseProgram(m_shader.getProgramID());
		
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

		glBindVertexArray(m_vaoId);
	
		glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(0);

	glUseProgram(0);
}