#pragma once
#include "EzyTex.h"
#include "FontAtlas.h"
class debug_font
{
public:
	debug_font(GLuint texId, FontAtlas& font);
	void load();
	void render(glm::mat4 &tmatrix, glm::mat4 &fMatrix); //ezyTex matrix and fontMatrix
	void update();
	~debug_font();

private:
	void genData();
	void addVertex(float x, float y, float z);
	void addVertex(glm::vec3 xyz);
	void addCharacter(int id);
	
	EzyTex m_tex;
	GLuint m_shaderId;
	
	GLuint m_vao;
	GLuint m_vbo;

	FontAtlas& m_font;
	std::vector<float> m_data;

	float depth;


};

