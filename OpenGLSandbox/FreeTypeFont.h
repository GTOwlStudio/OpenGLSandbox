#pragma once

#include <string>

#include <freetype\ft2build.h>
#include FT_FREETYPE_H
//#include <freetype\freetype.h>

#include <glm\glm.hpp>

#include "engine_shader.h"
#include "engine_texture.h"

class FreeTypeFont
{
public:
	FreeTypeFont();
	
	bool loadFont(std::string file, int pxSize);
	bool loadSystemFont();
	void setShaderProgram(engine_shader shaderProgram);
	void print(std::string text, int w, int y, int pxSize = -1);
	
	int getTextWidth(std::string text, int pxSize);
	void releaseFont();
	//~FreeTypeFont();

private:
	void createChar(int index);
	
	float charTexCoord[6];
	engine_texture charTextures[256];
	int advX[256], advY[256];
	int bearingX[256], bearingY[256];
	int charWidth[256], charHeight[256];
	int m_loadedPixelSize, m_newLine;

	bool m_loaded;

	GLuint m_vao;
	GLuint m_vbo;

	FT_Library ftLib;
	FT_Face ftFace;
	engine_shader *shaderProgram;

};

