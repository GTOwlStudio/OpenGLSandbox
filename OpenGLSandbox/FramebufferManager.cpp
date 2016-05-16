#include "FramebufferManager.h"

std::vector<GLuint> FramebufferManager::m_fbos;
std::vector<GLuint> FramebufferManager::m_tex;

void FramebufferManager::genFBOTAndTexture(GLuint &texId, GLuint &fboId, FramebufferInfo fbo)
{
	m_tex.emplace_back();
	
	float value = 1.0f;

	glGenTextures(1, &m_tex.back());
	texId = m_tex.back();
	printf("texID=%i w:%i h:%i\n", texId, fbo.tex_w, fbo.tex_h);
	glBindTexture(GL_TEXTURE_2D, m_tex.back());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, fbo.tex_w, fbo.tex_h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_fbos.emplace_back();
	glGenFramebuffers(1, &m_fbos.back());
	glBindFramebuffer(fbo.fbo_target, m_fbos.back());
		glFramebufferTexture2D(fbo.fbo_target, fbo.fbo_attachment, GL_TEXTURE_2D, m_tex.back(), 0);
	glBindFramebuffer(fbo.fbo_target, 0);
	
	fboId = m_fbos.back();
}

void FramebufferManager::cleanUp()
{
	for (unsigned int i = 0; i < m_fbos.size();i++) {
		glDeleteFramebuffers(1, &m_fbos[i]);
		glDeleteTextures(1, &m_tex[i]);
	}
}
