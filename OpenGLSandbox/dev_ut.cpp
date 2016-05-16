#include "dev_ut.h"



dev_ut::dev_ut() : m_fbo(0), m_t(0), m_shader("phyX/phyX_grid.vert", "phyX/phyX_grid.frag")
{
}

dev_ut::~dev_ut()
{
	glDeleteTextures(1, &m_t);
	glDeleteFramebuffers(1, &m_fbo);
}


void dev_ut::load()
{
	if (glIsTexture(m_t)) { glDeleteTextures(1, &m_t); }
	glGenTextures(1, &m_t);
	glBindTexture(GL_TEXTURE_2D, m_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (glIsFramebuffer(m_fbo)) { glDeleteFramebuffers(1, &m_fbo); }
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_t, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_shader.load();
}

GLuint dev_ut::getFBOId() const
{
	return m_fbo;
}

GLuint dev_ut::getTexId() const
{
	return m_t;
}

engine_shader dev_ut::getShader() const
{
	return m_shader;
}
