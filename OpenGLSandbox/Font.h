#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef WIN32
#include <GL/glew.h>

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <iostream>



class Font
{
public:
	Font();
	~Font();
	
private:
	/*FT_Face m_face;
	std::string m_fontname;*/

};

