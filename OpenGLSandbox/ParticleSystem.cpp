#include "ParticleSystem.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

ParticleSystem::ParticleSystem(float x, float y, float z, float w, float h, float depth, engine_window &window) : m_particles(0), m_grid(0),
m_vao(0), m_vbo(0), m_ibo(0), tp_vao(0), tp_vbo(0), tp_ibo(0),
m_boundsBytesSize(sizeof(float) * 8 * 3), m_indicesBytesSize(sizeof(unsigned int) * 24),
m_shader("shaders/particle_container.vert", "shaders/particle_container.frag"), m_shader_fbo("phyX/phyX_fbo.vert", "phyX/phyX_fbo.frag"),
m_phyX("phyX/phyX_dev.vert", "phyX/phyX_dev.frag"), m_shaderInit("shaders/couleur2D.vert", "shaders/couleur2D.frag"),
m_LastPos(0), m_PreviousPos(0), m_LastVel(0), m_PreviousVel(0),
m_fbo(0), m_window(window)//, m_renderBuffer(0)
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
	glDeleteVertexArrays(1, &m_uvao);

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
	float fpixels[3] = {0.5,0.5f,0.5f};
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 512*8, 64, 0, GL_RGB, GL_FLOAT,  0);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 10, 10, GL_RGB, GL_FLOAT, pixels);
	/*for (int y = 0; y < 512;y++) {
	Util::fillArrWithRandvf(512 * 3, pixels, 0.0, 1.0f);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0,y,512,1,GL_RGB,GL_FLOAT,pixels);
	//printf("y=%i\n", y);
	}*/
	glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,1,1,GL_RGB, GL_FLOAT,fpixels);
	//glTexSubImage2D(GL_TEXTURE_2D, 0,0,510,512,1,GL_RGB,GL_FLOAT,pixels);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 1, 1, 1, 1, GL_RGB, GL_FLOAT, pixels);
	//glTexSubImage2D();
	glBindTexture(GL_TEXTURE_2D, 0);

	if(glIsTexture(m_PreviousPos)) { glDeleteTextures(1, &m_PreviousPos); }
		glGenTextures(1, &m_PreviousPos);
		glBindTexture(GL_TEXTURE_2D, m_PreviousPos);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 512*8, 64, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,1,1,GL_RGB16F,GL_FLOAT,p);
		fpixels[0] = 0.5f; fpixels[1] = 0.5f; fpixels[2] = 0.5f;
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGB, GL_FLOAT, fpixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		//initParticle(PHYX_INITMODE_UNIFORM,64,64,64);

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
	m_shaderInit.load();

	
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

	if (glIsVertexArray(m_uvao)) { glDeleteVertexArrays(1, &m_uvao); }
	glGenVertexArrays(1, &m_uvao);
	glBindVertexArray(m_uvao);
	glBindVertexArray(0);

	texProcessorInit();

}

void ParticleSystem::physX(glm::mat4 &projection, glm::mat4 &modelview) {
	glUseProgram(m_phyX.getProgramID());
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
	glBindVertexArray(m_uvao);
	glBindTexture(GL_TEXTURE_2D, m_PreviousPos);
	glDrawArrays(GL_POINTS,0,262144);
	//glDrawArrays(GL_POINTS, 0, 44);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

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

void ParticleSystem::texProcess(GLuint const& texture, GLuint const& fbo, engine_shader const& processShader, size_t texW, size_t texH)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glViewport(0,0,texW, texH);
	glUseProgram(processShader.getProgramID());

	glBindVertexArray(tp_vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	glViewport(0,0,m_window.getWidth(), m_window.getHeight());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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

/*bool ParticleSystem::copyTexture(GLuint src, GLuint des)
{
	if (glIsTexture(src) && glIsTexture(des)) { 

		return true; 
	}
	return false;
}*/

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

void ParticleSystem::initParticle(PhyxEnum mode, unsigned int sx, unsigned int sy, unsigned int sz)
{
	//printf("sx=%i sy=%i\n", sx,sy);
	//unsigned int texW = 512;
	//unsigned int texH = 512;
	//GLuint tmpVBO;
	//GLuint tmpIBO;
	//GLuint tmpVAO;
	//float xPos=0;
	//float yPos = 0;
	//float *tmpCoords = new float[sz*8];
	//float *tmpColors = new float[sz * 3];
	//unsigned int *tmpIndex = new unsigned int[sz*2*3];
	//unsigned int coordsBytesSize = sz*8*sizeof(float);
	//printf("coords length = %i\n", sz*8);
	//unsigned int colorsBytesSize = sz*3*sizeof(float);
	//float tmpQuad[8] = {0.0f,0.0f,	0.0f,(float)sy,		(float)sx,(float)sy,	(float)sx,0.0f};
	//float tmpQColor[12] = {0.0f,0.0f,1.0f,	0.0f,1.0f,1.0f,	1.0f,1.0f,1.0f,	1.0f,0.0f,1.0f};
	//unsigned int tmpQIndice[6] = {0,1,2,0,2,3};
	////float tmpQuad[8] = {0.0,1.0,	2.0,3.0,	4.0,5.0,	6.0,7.0};
	//printf("cl + co /3=%i\n", (sz*5)/3);
	//for (unsigned int i = 0; i < sz;i++) {
	//	//Coord Copy
	//	for (int t = 0; t < 4;t++) {
	//		/*tmpCoords[i + (2 * t)] = (tmpQuad[t * 2] + xPos) / (float)texW;
	//		tmpCoords[i + (2 * t) + 1] = (tmpQuad[(2 * t) + 1] + yPos) / (float)texH;*/
	//		tmpCoords[(i*2)+ t] = (tmpQuad[t * 2] + xPos) / (float)texW;
	//		tmpCoords[(2*i)+t + 1] = (tmpQuad[(2 * t) + 1] + yPos) / (float)texH;
	//		tmpColors[i + (3 * t)] = tmpQColor[t * 3];
	//		tmpColors[i + (3 * t) + 1] = tmpQColor[(t * 3) + 1];
	//		tmpColors[i + (3 * t) + 2] = (float)i/(float)sz;
	//		//printf("tmpColors[%i] = %f\t%f\t%f\n", i, tmpColors[i+(3*t)], tmpColors[i + (3 * t)+1], tmpColors[i + (3 * t)+2]);
	//		/*tmpCoords[i + (2 * t)] = i+(2*t);
	//		tmpCoords[i + (2 * t) + 1] = i+(2*t)+1;*/
	//		//printf("tmpQuad[%i]=%f\ntmpQuad[%i]=%f\n", (2 * t), tmpQuad[(2 * t)], (2 * t) + 1, tmpQuad[(2 * t) + 1]);
	//		printf("tmpCoords[%i]=%f\t%f\n",i+(2*t), tmpCoords[i + (2 * t)], tmpCoords[i + (2 * t)+1]);
	//	}
	//	
	//	//Index Copy
	//	for (int t = 0; t < 6;t++) {
	//		tmpIndex[(6*i)+t] = tmpQIndice[t]+(6*i);
	//		//printf("tmpIndex[%i]=%i\n",(6*i)+t, tmpIndex[(6*i)+t]);
	//	}
	//	xPos += sx;
	//	if (xPos>texW) {
	//		xPos = 0.0f;
	//		yPos += sy;
	//		//printf("here\n");
	//	}
	//
	//}
	//
	//glClear(GL_COLOR_BUFFER_BIT);
	//
	//glGenVertexArrays(1, &tmpVAO);
	//glBindVertexArray(tmpVAO);
	//
	//glGenBuffers(1, &tmpIBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpIBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sz*6*sizeof(unsigned int), tmpIndex, GL_STATIC_DRAW);
	//printf("sz*8*sizeof(unsigned int)=%i\n", sz*6);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &tmpVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
	//glBufferData(GL_ARRAY_BUFFER, coordsBytesSize+colorsBytesSize,0, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, coordsBytesSize, tmpColors);
	//glBufferSubData(GL_ARRAY_BUFFER,coordsBytesSize,colorsBytesSize, tmpColors);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,0,(void*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,BUFFER_OFFSET(coordsBytesSize));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//glBindVertexArray(0);

	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	//glBindVertexArray(tmpVAO);
	//glUseProgram(m_shaderInit.getProgramID());
	////glDrawElements(GL_TRIANGLES, sz * 6,GL_UNSIGNED_INT,tmpIndex);
	//glDrawElements(GL_TRIANGLES, sz*6, GL_UNSIGNED_INT, (void*)0);
	//glUseProgram(0);
	//glBindVertexArray(tmpVAO);
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	//glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

	//glDeleteVertexArrays(1, &tmpVAO);
	//glDeleteBuffers(1, &tmpVBO);
	//glDeleteBuffers(1, &tmpIBO);
	//delete[] tmpCoords;
	//delete[] tmpColors;
	//delete[] tmpIndex;

	//unsigned int i = 0;
	//unsigned int ox;
	//unsigned int oy;
	//float pixels[3];
	//unsigned int texW = 512;
	//unsigned int texH = 512;
	//unsigned int size = 64;
	//unsigned int tmp = 0;
	//if (mode==PHYX_INITMODE_UNIFORM) {
	//	glBindTexture(GL_TEXTURE_2D, m_PreviousPos);

	//	for (size_t z = 0; z < size;z++) {
	//		for (size_t y = 0; y < size;y++) {
	//			for (size_t x = 0; x < size;x++) {
	//				ox = MathUtil::util3dTex_u(x, z, size, texW);
	//				tmp = floor(ox/texW);
	//				ox -= tmp*texW;
	//				oy = MathUtil::util3dTex_v(x, y, size, texW)+(tmp*size);
	//				pixels[0] = (float)x / (float)size;
	//				pixels[1] = (float)y / (float)size;
	//				pixels[2] = (float)z / (float)size;
	//				glTexSubImage2D(GL_TEXTURE_2D, 0,ox,oy,1,1,GL_RGB,GL_FLOAT,pixels);
	//			}
	//		}
	//	}
	//	printf("\nDone.");

	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}
	unsigned int ox;
	unsigned int oy;
	float pixels[3];
	unsigned int texW = 4096;
	unsigned int texH = 64;
	unsigned int size = sx;
	
	if (mode == PHYX_INITMODE_UNIFORM) {
	glBindTexture(GL_TEXTURE_2D, m_PreviousPos);

	for (size_t z = 0; z < size; z++) {
		for (size_t y = 0; y < size; y++) {
			for (size_t x = 0; x < size; x++) {
				ox = MathUtil::util3dTex_u(x, z, size, texW);
				oy = MathUtil::util3dTex_v(x, y, size, texW);
				pixels[0] = (float)x / (float)size;
				pixels[1] = (float)y / (float)size;
				pixels[2] = (float)z / (float)size;
				glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, 1, 1, GL_RGB, GL_FLOAT, pixels);
			}
		}
	}
	printf("\nDone.");

	glBindTexture(GL_TEXTURE_2D, 0);
}
}

GLuint ParticleSystem::getFBOId() const
{
	return m_fbo;
}

GLuint ParticleSystem::getFBOtexId() const
{
	return m_PreviousPos;
}

void ParticleSystem::dev_reloadPhyxShader()
{
	m_phyX.load();
}
