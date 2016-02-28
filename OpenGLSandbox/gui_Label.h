#pragma once

#include "gui_Object.h"
#include "FontAtlas.h"
#include "FileUtil.h"
#include "Util.h"

#include <map>


enum LABEL_POS_MODE {
	LABEL_POS_NONE = 0, //USER Defined
	LABEL_POS_CENTERED = 1 //Centered on the parent
};

class gui_Label : public gui_Object
{
public:
	gui_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth,float  r, float g, float b);
	gui_Label(std::string text, FontAtlas &atlas, float x, float y, float depth,float  r, float g, float b);
	gui_Label& operator=(gui_Label const& labelToCopy);

	

	//gui_Label(std::string text, FontAtlas &font, float x, float y, float depth, LABEL_POS_MODE  posmode);
	~gui_Label();
	void load();
	void update();
	//void updateVBO(void* datas, unsigned int bytesSize, unsigned int offset);
	//void render(glm::mat4 &projection);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setText(std::string text);
	void replace(size_t first, size_t last, std::string text);
	void setParameter(unsigned int parameter, int value);
	void setPosition(float x, float y);
	void setBounds(float w, float h);
	void move(float relX, float relY);
	//void setMaxWidth();
	FontAtlas* getFont() const;
	std::string getText() const;

	void setShaderSource(std::string vert, std::string frag);

private:
	void updateVBO(void* datas, unsigned int bytesSize, unsigned int offset);
	std::string m_text; //The text of the label
	FontAtlas *m_fontatlas; //FontAtlas containing the location of the character in the font atlas and the font atlas texture
	//int m_max;

	engine_shader m_shader;
	GLuint m_vboID;
	GLuint m_vaoID;
	
	float m_x, m_y,m_sx, m_sy;

	unsigned int m_textSize;
	unsigned int m_coordsBytesSize;
	unsigned int m_colorsBytesSize;
	unsigned int m_texCoordsBytesSize;
	
	glm::vec4 *m_coord; //Contains tex coords of each letter in 
	float *m_coords; //Contains the coords of the quad
	float *m_texCoords; //Contains the tex coords of the each letter in atlas
	float *m_color;

	float m_depth;
	
	float dev_vert[18];
	unsigned int dev_vertSize;
	float dev_tex[12];
	unsigned int dev_texSize;

	int m_nbreOfParameter; //Nombre de paramtre
/*	std::vector<int> m_locationOfParamater; //un tableau qui contien les locations dans la string des paramatres
	std::vector<float> m_value;*/
	std::map<int, float> m_parameters;
	void initParameter(std::string const& input);

};

