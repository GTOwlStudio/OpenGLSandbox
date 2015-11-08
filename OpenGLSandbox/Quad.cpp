#include "Quad.h"

// Macro utile au VBO

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Quad::Quad(float x, float y, float w, float h, float depth, std::string vert, std::string frag, std::string texture): m_verticesBytesSize(18*sizeof(float)), m_texCoordsBytesSize(12*sizeof(float)),
	m_shader(vert, frag),m_texture(texture)
{
	m_texture.load();

	m_shader.load();
	/*float tmpVertices[18] = {x,y,depth, x+w,y,depth, x,y+h,depth,
							x,y+h,depth, x+w,y,depth, x+w,y+h,depth};*/
	float tmpVertices[18] = {x,y+h,depth, x+w,y+h,depth,	x,y,depth,
							 x,y,depth,	 x+w,y+h,depth,		x+w,y,depth};

	/*float tmpTexCoords[12] = {1.0,0.0, 1.0,1.0, 0.0,1.0, 
								0.0,1.0, 1.0,1.0, 1.0, 0.0};*/

	float tmpTexCoords[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};

	for(int i=0;i<18;i++){
		//std::cout << i << ":"<< tmpVertices[i] << std::endl;
		m_vertices[i] = tmpVertices[i];
	}

	for (int i=0;i<12;i++){
		m_texCoords[i] = tmpTexCoords[i];
	}

}

Quad::Quad(float x, float y, float w, float h, float depth, std::string vert, std::string frag, GLuint textureID): m_verticesBytesSize(18*sizeof(float)), m_texCoordsBytesSize(12*sizeof(float)),
	m_shader(vert, frag),m_texture(textureID){
			m_texture.load();

	m_shader.load();
	/*float tmpVertices[18] = {x,y,depth, x+w,y,depth, x,y+h,depth,
							x,y+h,depth, x+w,y,depth, x+w,y+h,depth};*/
	float tmpVertices[18] = {x,y+h,depth, x+w,y+h,depth,	x,y,depth,
							 x,y,depth,	 x+w,y+h,depth,		x+w,y,depth};

	/*float tmpTexCoords[12] = {1.0,0.0, 1.0,1.0, 0.0,1.0, 
								0.0,1.0, 1.0,1.0, 1.0, 0.0};*/

	float tmpTexCoords[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};

	for(int i=0;i<18;i++){
		//std::cout << i << ":"<< tmpVertices[i] << std::endl;
		m_vertices[i] = tmpVertices[i];
	}

	for (int i=0;i<12;i++){
		m_texCoords[i] = tmpTexCoords[i];
	}
	
}

Quad::Quad(float vertices[18], std::string vert, std::string frag, std::string texture) : m_verticesBytesSize(18*sizeof(float)), m_texCoordsBytesSize(12*sizeof(float)),
	m_shader(vert, frag),m_texture(texture){
	
	m_shader.load();

	float tmpTexCoords[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};

	for(int i=0;i<18;i++){
		m_vertices[i] = vertices[i];
	}

	for (int i=0;i<12;i++){
		m_texCoords[i] = tmpTexCoords[i];
	}
}


Quad::Quad(float vertices[18], float texCoords[12], std::string vert, std::string frag, GLuint textureID) : m_verticesBytesSize(18*sizeof(float)), m_texCoordsBytesSize(12*sizeof(float)),
	m_shader(vert, frag),m_texture(textureID){

	m_shader.load();

	for(int i=0;i<18;i++){
		m_vertices[i] = vertices[i];
	}

	for (int i=0;i<12;i++){
		m_texCoords[i] = texCoords[i];
	}
}

Quad::Quad(float vertices[18], float texCoords[12], std::string vert, std::string frag, std::string texture) : m_verticesBytesSize(18*sizeof(float)), m_texCoordsBytesSize(12*sizeof(float)),
	m_shader(vert, frag),m_texture(texture){
	m_texture.load();
	m_shader.load();
	
	for(int i=0;i<18;i++){
		m_vertices[i] = vertices[i];
	}

	for (int i=0;i<12;i++){
		m_texCoords[i] = texCoords[i];
	}
}

Quad::~Quad()
{

	glDeleteBuffers(1,&m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Quad::load(){
	//std::cout << BUFFER_OFFSET(0);
	if (glIsBuffer(m_vboID)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vboID << std::endl;

		glDeleteBuffers(1, &m_vboID);
	}

	

	glGenBuffers(1, &m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		
		glBufferData(GL_ARRAY_BUFFER, m_verticesBytesSize+m_texCoordsBytesSize, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesBytesSize, m_vertices);
		glBufferSubData(GL_ARRAY_BUFFER, m_verticesBytesSize, m_texCoordsBytesSize, m_texCoords);
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
		glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesBytesSize));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*std::cout << "vboID = " << m_vboID << std::endl;
	std::cout << "vaoID = " << m_vaoID << std::endl;*/

}

void Quad::render(glm::mat4 &projection, glm::mat4 &modelview){
	
	glUseProgram(m_shader.getProgramID());
	   glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D, m_texture.getID());

            glDrawArrays(GL_TRIANGLES, 0, 6);

			glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
	glUseProgram(0);

}
