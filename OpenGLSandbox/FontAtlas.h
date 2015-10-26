#pragma once

#include "Font.h"
#include "engine_shader.h"
#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <array>

struct character_info{
	float ax; // advance.x
	float ay; // advance.y
  
	float bw; // bitmap.width;
	float bh; // bitmap.rows;
  
	float bl; // bitmap_left;
	float bt; // bitmap_top;
  
	float tx; // x offset of glyph in texture coordinates
	float ty; //y offset of glyph in textrure coordinates

};//c[128];

class FontAtlas
{
public:
	FontAtlas(std::string fontFace, int fontHeight);
	~FontAtlas();
	std::array<character_info, 128> const & getCharInfo() const;
	int getAtlasWidth() const;
	int getAtlasHeight() const;
	GLuint getTexID() const;
	float getATextWidth(std::string const& text);
	float getATextHeight(std::string const& text);
	int getFontHeight() const;
	//void renderText(const char *text, float x, float y, float sx, float sy, glm::mat4 &projection ,glm::mat4 &modelview);
	//bool init();
	
private:
	int m_width; //Atlas width
	int m_height; //Atlas height
	int m_font_height;
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glypSlot;
	GLuint m_texID;
	std::string m_fontFile;
	std::array<struct character_info, 128> m_charInfo;

	/*engine_shader m_shader;
	GLuint m_vbo;
	GLuint m_vao;*/


};

