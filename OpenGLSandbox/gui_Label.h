#pragma once

#include "gui_Object.h"
#include "FontAtlas.h"
#include "FileUtil.h"

enum LABEL_POS_MODE {
	LABEL_POS_NONE = 0, //USER Defined
	LABEL_POS_CENTERED = 1 //Centered on the parent
};

class gui_Label : public gui_Object
{
public:
	gui_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth,float  r, float g, float b);
	gui_Label(std::string text, FontAtlas &atlas, float x, float y, float depth,float  r, float g, float b);
	//gui_Label(std::string text, FontAtlas &font, float x, float y, float depth, LABEL_POS_MODE  posmode);
	~gui_Label();
	void load();
	void update();
	void updateVBO(void* datas, unsigned int bytesSize, unsigned int offset);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setPosition(float x, float y);
	void move(float relX, float relY);
	FontAtlas* getFont() const;

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
	unsigned int m_colorsBytesSize;
	unsigned int m_texCoordsBytesSize;
	
	glm::vec4 *m_coord; //Contains tex coords of each letter in atlas
	float *m_coords; //Contains the coords of the quad
	float *m_texCoords; //Contains the tex coords of the each letter in atlas

	float m_depth;
	
	float dev_vert[18];
	unsigned int dev_vertSize;
	float dev_tex[12];
	unsigned int dev_texSize;
};

