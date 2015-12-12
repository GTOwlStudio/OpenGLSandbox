#include "BSpline.h"


#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif
/*
#ifndef 
#define
#endif
*/
BSpline::BSpline(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b, float a) : m_controlBytesSize(6*sizeof(float)), m_colorsBytesSize(sizeof(float)*8), 
	m_pointsBytesSize(0), m_shader("shaders/spline.vert", "shaders/spline.frag"), m_vbo(0), m_vbo_spline(0) , m_vao(0)
{

	float tmpControl[6] = {x0,y0,z0, x1,y1,z1};
	
	for (int i = 0;i<6;i++){
		m_control.push_back(tmpControl[i]);
	}
	for (int i =0;i<2;i++){
		m_colors.push_back(r);
		m_colors.push_back(g);
		m_colors.push_back(b);
		m_colors.push_back(a);
	}
	
}


void BSpline::load(){
	m_shader.load();

	if (glIsBuffer(m_vbo)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vbo << std::endl;
		glDeleteBuffers(1, &m_vbo);
	}

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_controlBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_controlBytesSize, m_control.data());
	glBufferSubData(GL_ARRAY_BUFFER, m_controlBytesSize, m_colorsBytesSize, m_colors.data());
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
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_controlBytesSize));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void BSpline::render(glm::mat4 &mat){
	glUseProgram(m_shader.getProgramID());
	
	glBindVertexArray(m_vao);
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
	//glDrawArrays(GL_LINE_STRIP, 0, m_control.size()/3);
	glDrawArrays(GL_LINE_STRIP, 0, m_points.size()/3);
	glBindVertexArray(0);
	glUseProgram(0);
}

BSpline::~BSpline(void)
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_vbo_spline);
	glDeleteVertexArrays(1, &m_vao);
}


void BSpline::addControlPoint(float x, float y, float z){
	m_control.push_back(x);
	m_control.push_back(y);
	m_control.push_back(z);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	//printf("m_colors[m_colors.size()-4]=%f\n", m_colors[m_colors.size()-4]);
	m_colors.push_back(m_colors[m_colors.size()-4]);
	m_controlBytesSize += sizeof(float)*3;
	m_colorsBytesSize += sizeof(float)*4;
	glDeleteBuffers(1, &m_vbo);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_controlBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_controlBytesSize, m_control.data());
	glBufferSubData(GL_ARRAY_BUFFER, m_controlBytesSize, m_colorsBytesSize, m_colors.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_controlBytesSize));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void BSpline::updateVBO(void* datas,unsigned int bytesSize, unsigned int offset){
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

float BSpline::bezierCubic(float v0, float v1, float v2, float v3, float t){
	
	return (v0*std::pow((1-t),3))  + ((3*v1*t)*std::pow(1-t, 2)) + (3*v2*std::pow(t,2)*(1-t)) + (v3*pow(t, 3));

}

void BSpline::generateSpline(float step){
	//int i =0;
	for (float t=0.0;t<1.0;t+=step){
		m_points.push_back(bezierCubic(m_control[0], m_control[3], m_control[6], m_control[9], t));
		m_points.push_back(bezierCubic(m_control[1], m_control[4], m_control[7], m_control[10], t));
		m_points.push_back(bezierCubic(m_control[2], m_control[5], m_control[8], m_control[11], t));
		/*m_points.push_back(bezierCubic(m_control[0], t));
		m_points.push_back(bezierCubic(m_control[1], t));
		m_points.push_back(bezierCubic(m_control[2], t));
		m_points.push_back(bezierCubic(m_control[3], t));*/
		//i+=4;
	}
	printf("%i\n",m_control.size());
	//printf("x:%f y:%f z:%f\n", );
	m_points.push_back(m_control[m_control.size()-3]);
	m_points.push_back(m_control[m_control.size()-2]);
	m_points.push_back(m_control[m_control.size()-1]);
	
	printf("Spline Generated, size=%i\n", m_points.size());
	dev_generateSplineUpdate(m_points.size()*sizeof(float));
}

void BSpline::dev_generateSplineUpdate(int bytesSize){
	
	m_pointsBytesSize = bytesSize;

	if (glIsBuffer(m_vbo_spline)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vbo << std::endl;
		glDeleteBuffers(1, &m_vbo_spline);
	}

	glGenBuffers(1, &m_vbo_spline);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_spline);
	glBufferData(GL_ARRAY_BUFFER, m_pointsBytesSize, m_points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_spline);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_controlBytesSize));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glDeleteBuffers(1,);

}