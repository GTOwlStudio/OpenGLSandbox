#include "ParticleSystem.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

ParticleSystem::ParticleSystem(float x, float y, float z, float w, float h, float depth) : m_particles(0), m_grid(0),
m_vao(0), m_vbo(0), m_ibo(0), tp_vao(0), tp_vbo(0), tp_ibo(0),
m_boundsBytesSize(sizeof(float) * 8 * 3), m_indicesBytesSize(sizeof(unsigned int) * 24),
m_shader("shaders/particle_container.vert", "shaders/particle_container.frag"), m_shader_fbo("phyX/phyX_fbo.vert", "phyX/phyX_fbo.frag"),
m_phyX("phyX/phyX_dev.vert", "phyX/phyX_dev.frag"),
m_LastPos(0), m_PreviousPos(0), m_LastVel(0), m_PreviousVel(0),
m_fbo(0)//, m_renderBuffer(0)
{

	unsigned int tmpEdgesIndices[24] = {0,1,	1,2,	2,3,	3,0, //One Quad
								   4,5, 5,6,	6,7,	7,4, //Second Quad
									0,4, 1,5,	2,6,	3,7}; //Edge Between the 2 Quad

	for (int i = 0; i < 24;i++) {
		m_edgesIndices[i] = tmpEdgesIndices[i];
	}

	float tmpBounds[24] = {x,y,z,		x,y+h,z,		x+w,y+h,z,			x+w,y,z,
							x,y,z+h,	x,y + h,z+h,	x + w,y + h,z+h,	x + w,y,z+h};
	for (int i = 0; i < 24;i++) {
		m_bounds[i] = tmpBounds[i];
	}
}


ParticleSystem::~ParticleSystem()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);

	glDeleteBuffers(1, &tp_vbo);
	glDeleteBuffers(1, &tp_ibo);
	glDeleteVertexArrays(1, &tp_vao);

	glDeleteTextures(1, &m_particles);
	glDeleteTextures(1, &m_PreviousPos);
	glDeleteTextures(1, &m_LastPos);
	glDeleteTextures(1, &m_PreviousVel);
	glDeleteTextures(1, &m_LastVel);
	glDeleteFramebuffers(1, &m_fbo);

	
}

void ParticleSystem::load() {
	
	unsigned char tmpp[1 * 3] = {255,255,255};
	float fpixels[3] = {2.0f,2.0f,2.0f};
	for (int i = 0; i < 3; i++) {
		p[i] = tmpp[i];
	}
	//Util::fillArrWithRandvui(3,p,0,256);
	float pixels[512*3];// = { 1.0f / 255.0f, 1.0f / 255.0f, 1.0f / 255.0f };
	m_drawBuffers[0] = GL_COLOR_ATTACHMENT0;
	
	/*pixels[0]=1.0/255.0f;
	pixels[1] = 1.0 / 255.0f;
	pixels[2] = 1.0 / 255.0f;
	pixels[3] = 50.0 / 255.0f;
	pixels[4] = 50.0 / 255.0f;
	pixels[5] = 50.0 / 255.0f;*/
	if (glIsTexture(m_LastPos)) {
		glDeleteTextures(1, &m_LastPos);
	}
	glGenTextures(1, &m_LastPos);
	glBindTexture(GL_TEXTURE_2D, m_LastPos);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT,  0);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 10, 10, GL_RGB, GL_FLOAT, pixels);
	for (int y = 0; y < 512;y++) {
	Util::fillArrWithRandvf(512 * 3, pixels, 0.0, 1.0f);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0,y,512,1,GL_RGB,GL_FLOAT,pixels);
	//printf("y=%i\n", y);
	}
	glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,1,1,GL_RGB, GL_FLOAT,fpixels);
	//glTexSubImage2D(GL_TEXTURE_2D, 0,0,510,512,1,GL_RGB,GL_FLOAT,pixels);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 1, 1, 1, 1, GL_RGB, GL_FLOAT, pixels);
	//glTexSubImage2D();
	glBindTexture(GL_TEXTURE_2D, 0);

	if(glIsTexture(m_PreviousPos)) { glDeleteTextures(1, &m_PreviousPos); }
		glGenTextures(1, &m_PreviousPos);
		glBindTexture(GL_TEXTURE_2D, m_PreviousPos);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,1,1,GL_RGB,GL_FLOAT,p);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (glIsFramebuffer(m_fbo)) { glDeleteFramebuffers(1, &m_fbo); }
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		glFramebufferTexture(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,m_PreviousPos,0);
		//glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_FRONT, m_PreviousPos, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		
	
		/*glGenTextures(1, &m_particles);
	glBindTexture(GL_TEXTURE_2D, m_particles);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,1024,1024,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	//if (){}
	//glGenTextures();

	m_shader.load();
	m_shader_fbo.load();
	m_phyX.load();

	
	if (glIsVertexArray(m_vao)) { glDeleteVertexArrays(1, &m_vao); }
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray( m_vao);

		if (glIsBuffer(m_ibo)) { glDeleteBuffers(1, &m_ibo);}
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesBytesSize, m_edgesIndices, GL_STATIC_DRAW);

		if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_boundsBytesSize, m_bounds, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	texProcessorInit();

}

void ParticleSystem::physX(glm::mat4 &projection, glm::mat4 &modelview) {
	/*glBindTexture(GL_TEXTURE_2D, m_PreviousPos);
	glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,1,1,GL_RGB,GL_UNSIGNED_BYTE,p);
	glBindTexture(GL_TEXTURE_2D, 0);*/
	//glUseProgram(m_phyX.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

	
	//glDrawBuffers(1, &GL_COLOR_ATTACHMENT0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	//glBindTexture(GL_TEXTURE_2D, m_LastPos);
	//glDrawBuffers(1, m_drawBuffers);
	texProcess();
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	/*glBindVertexArray(m_vao);
	//glBindTexture(GL_TEXTURE_2D, m_LastPos);
	//glDrawElements(GL_POINTS, 24, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_POINTS, 0, 2);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);*/
	

	//glUseProgram(0);
	/*glBindTexture(GL_TEXTURE_2D, m_PreviousPos);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, p);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void ParticleSystem::render(glm::mat4 &projection, glm::mat4 &modelview) {

	glUseProgram(m_shader.getProgramID());

	

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
	
	glBindVertexArray(m_vao);

		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glUseProgram(0);
	
}

void ParticleSystem::texProcess()
{
	glUseProgram(m_phyX.getProgramID());

	glBindVertexArray(tp_vao);
	glBindTexture(GL_TEXTURE_2D, m_LastPos);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}

void ParticleSystem::fboDisplay()
{
	glUseProgram(m_shader_fbo.getProgramID());
	glBindVertexArray(tp_vao);
	glBindTexture(GL_TEXTURE_2D,m_PreviousPos);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
	glBindTexture(GL_TEXTURE_2D,0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void ParticleSystem::texProcessorInit() {
	tp_verticesBytesSize = sizeof(float) * 8;
	tp_texCoordsBytesSize = sizeof(float) * 8;
	tp_indicesBytesSize = sizeof(unsigned int) * 6;
	
	float depth = 0.2f;
	//float tmpVertices[12] = {-0.5,-0.5,depth,	-0.5,0.5,depth,		0.5,0.5,depth,	0.5,-0.5,depth};
	//float tmpVertices[8] = { -0.5,-0.5,	-0.5,0.5,	0.5,0.5,	0.5,-0.5 };
	float tmpVertices[8] = {-1.0,-1.0,	-1.0,1.0,	1.0,1.0,	1.0,-1.0 };
	float tmpTexCoords[8] = {0.0,0.0, 0.0,1.0, 1.0,1.0, 1.0,0.0};
	unsigned int tmpIndices[6] = {0,1,2,0,2,3};

	for (int i = 0; i < 8;i++) {
		tp_vertices[i] = tmpVertices[i];
	}

	for (int i = 0; i < 8; i++) {
		tp_texCoords[i] = tmpTexCoords[i];
	}

	for (int i = 0; i < 6;i++) {
		tp_indices[i] = tmpIndices[i];
	}

	if (glIsVertexArray(tp_vao)) { glDeleteVertexArrays(1, &tp_vao); }
	glGenVertexArrays(1, &tp_vao);
	glBindVertexArray(tp_vao);

	if (glIsVertexArray(tp_ibo)) { glDeleteVertexArrays(1, &tp_ibo); }
	glGenBuffers(1, &tp_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tp_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tp_indicesBytesSize, tp_indices, GL_STATIC_DRAW);

	if (glIsVertexArray(tp_vbo)) { glDeleteVertexArrays(1, &tp_vbo); }
	glGenBuffers(1, &tp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tp_vbo);
	glBufferData(GL_ARRAY_BUFFER, tp_verticesBytesSize+tp_texCoordsBytesSize, tp_vertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, tp_verticesBytesSize, tp_texCoordsBytesSize, tp_texCoords);

	glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 0,(void*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tp_verticesBytesSize));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}