#include "QuadC.h"


#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

QuadC::QuadC(float x, float y, float w, float h, float depth, float r, float g, float b, float a): m_verticesBytesSize(18*sizeof(float)), m_colorsBytesSize(24*sizeof(float)), 
	m_shader("shaders/colors.vert", "shaders/colors.frag")
{
	//m_texture.load();
	//printf("m_w=%f m_h=%f\n", w,h);
	m_shader.load();
	/*float tmpVertices[18] = {x,y,depth, x+w,y,depth, x,y+h,depth,
							x,y+h,depth, x+w,y,depth, x+w,y+h,depth};*/
	float tmpVertices[18] = {x,y+h,depth, x+w,y+h,depth,	x,y,depth,
							 x,y,depth,	 x+w,y+h,depth,		x+w,y,depth};

	/*float tmpTexCoords[12] = {1.0,0.0, 1.0,1.0, 0.0,1.0, 
								0.0,1.0, 1.0,1.0, 1.0, 0.0};*/

	/*float tmpTexCoords[24] = {r,g,b,a, r,g,b,a, r,b,g,a, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};*/

	for(int i=0;i<18;i++){
		//std::cout << i << ":"<< tmpVertices[i] << std::endl;
		m_vertices[i] = tmpVertices[i];
	}

	for (int i=0;i<24;i+=4){
		m_colors[i] = r;
		m_colors[i+1] = g;
		m_colors[i+2] = b;
		m_colors[i+3] = a;
	}

}

QuadC::QuadC(float vertices[18], std::string vert, std::string frag, float colors[24]) : m_verticesBytesSize(18*sizeof(float)), m_colorsBytesSize(24*sizeof(float)),
	m_shader(vert, frag){
	
	m_shader.load();

	/*float tmpTexCoords[18] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};*/

	for(int i=0;i<18;i++){
		m_vertices[i] = vertices[i];
	}

	for (int i=0;i<24;i++){
		m_colors[i] = colors[i];
	}
}


void QuadC::update(){
	std::printf("Not coded yet maybe nerver don't use QuadC::update() ");
}

QuadC::~QuadC()
{

	glDeleteBuffers(1,&m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void QuadC::updateVBO(void* datas, unsigned int bytesSize, unsigned int offset){
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	void *VBOAddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (VBOAddress==NULL){
		std::cout << "ERROR : while VBO recuperation" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}

	memcpy((char*)VBOAddress + offset, datas,bytesSize);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	VBOAddress = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void QuadC::load(){
	//std::cout << BUFFER_OFFSET(0);
	if (glIsBuffer(m_vboID)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vboID << std::endl;

		glDeleteBuffers(1, &m_vboID);
	}

	

	glGenBuffers(1, &m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		
		glBufferData(GL_ARRAY_BUFFER, m_verticesBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesBytesSize, m_vertices);
		glBufferSubData(GL_ARRAY_BUFFER, m_verticesBytesSize, m_colorsBytesSize, m_colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (glIsVertexArray(m_vaoID)==GL_TRUE){
		std::cout << "glIsVertexArray() = GL_TRUE vaoID = " << m_vaoID << std::endl;
		glDeleteVertexArrays(1, &m_vaoID);
	}

	glGenVertexArrays(1, &m_vaoID);

	glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesBytesSize));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*std::cout << "vboID = " << m_vboID << std::endl;
	std::cout << "vaoID = " << m_vaoID << std::endl;*/

}

void QuadC::render(glm::mat4 &projection, glm::mat4 &modelview){
	
	glUseProgram(m_shader.getProgramID());
	   glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

            glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
	glUseProgram(0);

}

void QuadC::setPosition(float x, float y){
	//printf("x=%f y=%f\n", x, y);
	float tmp_W=m_vertices[3]-m_vertices[0];
	float tmp_H=m_vertices[1]-m_vertices[7];
	
	float tmpVertices[12] = {x,y+tmp_H, x+tmp_W,y+tmp_H,	x,y,
							 x,y,	 x+tmp_W,y+tmp_H,		x+tmp_W, y};
	int offset=0;
	for(int i=0;i<12;i+=2){
		m_vertices[i+offset] = tmpVertices[i];//X
		m_vertices[i+1+offset] = tmpVertices[i+1];//Y
		offset++;
	}
	updateVBO(m_vertices, m_verticesBytesSize, 0);

}

void QuadC::setBounds(float w, float h){
	float tmp_X = m_vertices[0];
	float tmp_Y = m_vertices[7];
//	printf("x=%f y=%f\n", tmp_X, tmp_Y);
	float tmpVertices[12] = {tmp_X,tmp_Y+h, tmp_X+w,tmp_Y+h,	tmp_X,tmp_Y,
							 tmp_X,tmp_Y,	 tmp_X+w,tmp_Y+h,		tmp_X+w, tmp_Y};
	int offset=0;
	for(int i=0;i<12;i+=2){
		m_vertices[i+offset] = tmpVertices[i];//X
		m_vertices[i+1+offset] = tmpVertices[i+1];//Y
		offset++;
	}
	updateVBO(m_vertices, m_verticesBytesSize, 0);

}