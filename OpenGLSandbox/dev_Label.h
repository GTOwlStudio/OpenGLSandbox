#pragma once

#include "gui_Object.h"
#include "FontAtlas.h"
#include "FileUtil.h"
#include "Util.h"

/*enum LABEL_POS_MODE {
	LABEL_POS_NONE = 0, //USER Defined
	LABEL_POS_CENTERED = 1 //Centered on the parent
};*/

class dev_Label : public gui_Object
{
public:
	dev_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth,float  r, float g, float b);
	dev_Label(std::string text, FontAtlas &atlas, float x, float y, float depth,float  r, float g, float b);
	dev_Label& operator=(dev_Label const& labelToCopy);
	//gui_Label(std::string text, FontAtlas &font, float x, float y, float depth, LABEL_POS_MODE  posmode);
	~dev_Label();
	void load();
	void update();
	void updateVBO(void* datas, unsigned int bytesSize, unsigned int offset);
	//void render(glm::mat4 &projection);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setText(std::string text);
	void setPosition(float x, float y);
	void setBounds(float w, float h);
	void move(float relX, float relY);
	//void setMaxWidth();
	FontAtlas* getFont() const;
	std::string getText() const;

	void setShaderSource(std::string vert, std::string frag);

private:
	std::string m_text; //The text of the label
	FontAtlas *m_fontatlas; //FontAtlas containing the location of the character in the font atlas and the font atlas texture
	//int m_max;

	engine_shader m_shader;
	GLuint m_vaoID;
	GLuint m_vboID;
	GLuint m_iboID;
	
	
	float m_x, m_y,m_sx, m_sy;

	unsigned int m_textSize;
	unsigned int m_coordsBytesSize;
	unsigned int m_colorsBytesSize;
	unsigned int m_texCoordsBytesSize;
	unsigned int m_indicesBytesSize;
	
	glm::vec4 *m_coord; //Contains tex coords of each letter in 
	float *m_coords; //Contains the coords of the quad
	float *m_texCoords; //Contains the tex coords of the each letter in atlas
	float *m_color;
	unsigned int *m_indices;

	float m_depth;
	
	float dev_vert[18];
	unsigned int dev_vertSize;
	float dev_tex[12];
	unsigned int dev_texSize;
};

