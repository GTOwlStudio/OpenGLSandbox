#include "dev_ro.h"



dev_ro::dev_ro(float x, float y, float w, float h) : m_shaderInit("phyX/phyX_basic.vert","phyX/phyX_basic.frag")
{
	float tmpQuad[8] = {0.0f,0.0f,	0.0f,h,		w,h,	w,0.0f};
	float tmpQColor[12] = {0.0f,0.0f,1.0f,	0.0f,1.0f,1.0f,	1.0f,1.0f,1.0f,	1.0f,0.0f,1.0f};
	unsigned int tmpQIndice[6] = {0,1,2,0,2,3};
	for (int i = 0; i < 8;i++) {
		m_coords[i] = tmpQuad[i];
	}
	for (int i = 0; i < 12; i++) {
		m_colors[i] = tmpQColor[i];
	}
	for (int i = 0; i < 6; i++) {
		m_indices[i] = tmpQIndice[i];
	}
}


dev_ro::~dev_ro()
{
}

void dev_ro::load()
{
	m_shaderInit.load();
}

void dev_ro::render()
{
	glUseProgram(m_shaderInit.getProgramID());
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_coords);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glDrawElements(GL_TRIANGLES, sz * 6,GL_UNSIGNED_INT,tmpIndex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, m_indices);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
