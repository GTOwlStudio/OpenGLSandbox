#include "debug_font.h"



debug_font::debug_font(GLuint texId, FontAtlas& font) : m_tex(texId), m_shaderId(RessourcesManager::getShaderId("vertex_only")), m_vao(0), m_vbo(0), m_font(font), depth(0.4f)
{
}

void debug_font::load()
{
	m_tex.load();
	genData();
	//addVertex(0.0f, 0.0f, 0.4f);
	if (glIsVertexArray(m_vao)) {glDeleteVertexArrays(1, &m_vao);}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_data.size()*sizeof(float), m_data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	
	glBindVertexArray(0);

}



void debug_font::render(glm::mat4 & matrix, glm::mat4 &fmatrix)
{

	m_tex.render(matrix);
	glUseProgram(m_shaderId);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderId, "matrix"), 1, GL_FALSE, glm::value_ptr(fmatrix));

	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_data.size());
	glBindVertexArray(0);

	glUseProgram(0);

	

}


debug_font::~debug_font()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void debug_font::genData()
{
	for (int i = 32; i < 128;i++) {
		//printf("%i%c\t",i, i);
		//addVertex(m_font.getCharInfo()[i].tx, m_font.getCharInfo()[i].ty, 0.5f);
		addCharacter(i);
	}
	Util::conceptor("\ndebug font genData report : data size = %i\n", m_data.size());
}


void debug_font::addCharacter(int id)
{
	float tx =	 m_font.getCharInfo()[id].tx;
	float ty =	 m_font.getCharInfo()[id].ty;
	float x(tx/*+	 m_font.getCharInfo()[id].bl*/); //bl
	float y(ty/*+  m_font.getCharInfo()[id].ay + m_font.getCharInfo()[id].bt*/); // ay+bt
	float w(tx - m_font.getCharInfo()[id].bw/*m_font.getCharInfo()[id].bl*/); //bl+bw
	float h(ty + m_font.getCharInfo()[id].bh);//ay+bt+bh
	if (id==84) {
		Util::green("%f %f %f %f\n", x/m_font.getAtlasWidth(),y / m_font.getAtlasHeight(),w  / m_font.getAtlasWidth(),h / m_font.getAtlasHeight());
		Util::green("x:%f y:%f w:%f h:%f tw:%i th:%i", x,y,w,h,m_font.getAtlasWidth(), m_font.getAtlasHeight());
	}
	addVertex(x, y, depth);
	addVertex(x, h, depth);
	addVertex(w, h, depth);
	//addVertex(w, y, depth);
}

void debug_font::addVertex(float x, float y, float z) {
	m_data.push_back(x);
	m_data.push_back(y);
	m_data.push_back(z);
}

void debug_font::addVertex(glm::vec3 xyz)
{
	m_data.push_back(xyz.x);
	m_data.push_back(xyz.y);
	m_data.push_back(xyz.z);
}


