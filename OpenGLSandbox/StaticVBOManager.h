#pragma once

#include "glheader.h"
#include <map>

class StaticVBOManager
{
public:
	static void init();
	static void genVBO(std::string name);
	static void cleanUp();
	static GLuint getVBO(GLuint sID); // The Id in this manager
private:
	static std::map<GLuint, std::string> vbo;

};

