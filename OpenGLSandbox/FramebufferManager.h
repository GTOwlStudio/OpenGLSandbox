#pragma once
#include <vector>
#include "glheader.h"


struct FramebufferInfo {
	GLenum fbo_target;
	GLenum fbo_attachment;
	GLenum tex_w, tex_h;
};

struct RenderbufferInfo {
	GLenum rbo_target;
	GLenum rbo_interformat;
	GLenum rbo_attachment;
};

class FramebufferManager
{
public:
	static void genFBOTAndTexture(GLuint &texId, GLuint &fboId, FramebufferInfo fInfo);
	static void genFBO(GLuint *texId, FramebufferInfo rboI, RenderbufferInfo rboi);
	static void cleanUp();

private:
	static std::vector<GLuint> m_fbos;
	static std::vector<GLuint> m_tex;
};

