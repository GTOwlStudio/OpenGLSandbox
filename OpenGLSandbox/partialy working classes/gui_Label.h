#pragma once

#include "FontAtlas.h"
#include "FileUtil.h"

class gui_Label
{
public:
	gui_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth,float  r, float g, float b);
	~gui_Label();
	void load();
	void render(glm::mat4 &projection, glm::mat4 &modelview);

private:
	std::string m_text; //The text of the label
	FontAtlas *m_fontatlas; //FontAtlas containing the location of the character in the font atlas and the font atlas texture

	engine_shader m_shader;
	GLuint m_vboID;
	GLuint m_vaoID;
	
	float m_x, m_y,m_sx, m_sy;
	float m_color[3];

	unsigned int m_textSize;
	unsigned int m_coordsBytesSize;
	
	glm::vec4 *m_coord; //Contains tex coords of each letter in atlas
	float *m_coords; //Contains the tex coords of the quad
	float m_depth;
	
	float dev_vert[18];
	unsigned int dev_vertSize;
	float dev_tex[12];
	unsigned int dev_texSize;
};

