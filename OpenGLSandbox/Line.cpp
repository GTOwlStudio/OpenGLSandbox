#include "Line.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Line::Line(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b, float a) : m_pointsBytesSize(6*sizeof(float)), m_colorsBytesSize(sizeof(float)*8), m_shader("shaders/line.vert", "shaders/line.frag"), m_vbo(0), m_vao(0)
{

	float tmpPoints[6] = {x0,y0,z0, x1,y1,z1};
	
	for (int i = 0;i<6;i++){
		m_points.push_back(tmpPoints[i]);
	}
	/*for (int i = 0;i<2;i++){
	m_colors[i*4] = r;
	m_colors[i*4+1] = g;
	m_colors[i*4+2] = b;
	m_colors[i*4+3] = a;
	}*/
	for (int i =0;i<2;i++){
		m_colors.push_back(r);
		m_colors.push_back(g);
		m_colors.push_back(b);
		m_colors.push_back(a);
	}
	
}


void Line::load(){
	m_shader.load();

	if (glIsBuffer(m_vbo)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vbo << std::endl;
		glDeleteBuffers(1, &m_vbo);
	}

	//float *p = &m_points[0];
	/*float* p = new float[m_points.size()];
	for (int i =0;i<m_points.size();i++){
		p[i] = m_points[i];
	}*/

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_pointsBytesSize, m_points.data());
	glBufferSubData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_colorsBytesSize, m_colors.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (glIsVertexArray(m_vao)==GL_TRUE){
		std::cout << "glIsVertexArray() = GL_TRUE vaoID = " << m_vao<< std::endl;
		glDeleteVertexArrays(1, &m_vao);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_pointsBytesSize));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void Line::render(glm::mat4 &mat){
	glUseProgram(m_shader.getProgramID());
	
	glBindVertexArray(m_vao);
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
	glDrawArrays(GL_LINE_STRIP, 0, m_points.size()/3);
	glBindVertexArray(0);
	glUseProgram(0);
}

Line::~Line(void)
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}


void Line::addPoints(float x, float y, float z){
	m_points.push_back(x);
	m_points.push_back(y);
	m_points.push_back(z);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	m_pointsBytesSize += sizeof(float)*3;
	m_colorsBytesSize += sizeof(float)*4;
	glDeleteBuffers(1, &m_vbo);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_pointsBytesSize, m_points.data());
	glBufferSubData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_colorsBytesSize, m_colors.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_pointsBytesSize));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Line::updateVBO(void* datas,unsigned int bytesSize, unsigned int offset){
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
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

unsigned int Line::getLineSized() const{
	return m_points.size();
}

void Line::setPoint(unsigned int id, float x, float y, float z){
	if (id*3<m_points.size()){
	printf("id*3=%i\n", id*3);
	m_points[id*3] = x;
	printf("id*3+1=%i\n", (id*3)+1);
	m_points[(id*3)+1] = y;
	printf("id*3+2=%i\n", (id*3)+2);
	m_points[(id*3)+2] = z;
	//WARNING
	float ncoords[3] = {x,y,z};
	updateVBO(ncoords, sizeof(float)*3, sizeof(float)*3*id);

	}
}