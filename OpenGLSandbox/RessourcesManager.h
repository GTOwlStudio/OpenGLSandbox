#pragma once

#include <map>
#include <string>
#include "engine_shader.h"
#include "Util.h"

class RessourcesManager
{
public:
	static void init();
	static void cleanUp();
	static void addShader(std::string vert, std::string frag, std::string sName);
	static GLuint getShaderId(std::string shaderName);
private:
	static std::map<std::string, GLuint> m_shadersNameAndId;
	static std::vector<engine_shader*> m_shaders;
};

