#include "dev_line.h"



dev_line::dev_line(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2) :
	m_coordsBytesSize(sizeof(float) * 9), m_indicesBytesSize(sizeof(unsigned int) * 4),
	m_vao(0), m_ibo(0), m_vbo(0),
	m_shader("shaders/line_dev.vert", "shaders/line_dev.frag")
{
	unsigned int tmpIndices[4] = {0, 1, 1,2};

	for (int i = 0; i < 4; i++) {
		m_indices[i] = tmpIndices[i];
	}

	float tmpCoords[9] = {x0,y0,z0,	x1,y1,z1,	x2,y2,z2};
	for (int i = 0; i < 9;i++) {
		m_coords[i] = tmpCoords[i];
	}
}


dev_line::~dev_line()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

void dev_line::load()
{
	m_shader.load();

	if (glIsVertexArray(m_vao)) { glDeleteVertexArrays(1, &m_vao); }
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

		if (glIsBuffer(m_ibo)) { glDeleteBuffers(1, &m_ibo); }
		
		glGenBuffers(1, &m_ibo);
		Util::conceptor("ibo=%i\n", m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesBytesSize, m_indices, GL_STATIC_DRAW);

		if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_coords, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void dev_line::render(glm::mat4 & projection, glm::mat4 & modelview)
{

	glUseProgram(m_shader.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
	
	glBindVertexArray(m_vao);
	
		glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (void*)0);
		//glDrawArrays(GL_LINE_STRIP, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);

}


