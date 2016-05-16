#include "RessourcesManager.h"

std::vector<engine_shader*> RessourcesManager::m_shaders;
std::map<std::string, GLuint> RessourcesManager::m_shadersNameAndId;


void RessourcesManager::init()
{
	Util::conceptor("RessourcesManager init");
	RessourcesManager::addShader("shaders/texture2d.vert", "shaders/texture2d.frag", "texture2d");
	RessourcesManager::addShader("shaders/dev_font.vert", "shaders/dev_font.frag", "dev_font");
	RessourcesManager::addShader("shaders/vertex_only.vert", "shaders/vertex_only.frag", "vertex_only");
	RessourcesManager::addShader("shaders/diffuse.vert", "shaders/diffuse.frag", "diffuse");
}

void RessourcesManager::cleanUp()
{
	for (unsigned int i = 0; i < RessourcesManager::m_shaders.size();i++) {
		delete RessourcesManager::m_shaders[i];
		RessourcesManager::m_shaders[i] = 0;
	}
}

void RessourcesManager::addShader(std::string vert, std::string frag, std::string sName)
{

	RessourcesManager::m_shaders.push_back(new engine_shader(vert,frag));
	RessourcesManager::m_shaders.back()->load();
	printf("shader\n", RessourcesManager::m_shaders.back()->getProgramID());
	RessourcesManager::m_shadersNameAndId.emplace(sName, RessourcesManager::m_shaders.back()->getProgramID());
}

GLuint RessourcesManager::getShaderId(std::string shaderName)
{
	Util::conceptor("%i\n", RessourcesManager::m_shadersNameAndId[shaderName]);
	return RessourcesManager::m_shadersNameAndId[shaderName];
}
