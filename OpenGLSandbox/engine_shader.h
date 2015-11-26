#pragma once

// Include Windows

#ifdef WIN32
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif


// Includes communs

#include <iostream>
#include <string>
#include <fstream>


// Classe engine_shader

enum SHADER_TYPE {

	SHADER_VERTEX_GEOMETRY_FRAGMENT = 0,
	SHADER_VGF = 0, //Vertex Geometry Fragment
	SHADER_VERTEX_FRAGMENT = 1,
	SHADER_VF = 1

};

class engine_shader
{
    public:

    engine_shader();
    engine_shader(engine_shader const &shaderACopier);
    engine_shader(std::string vertexSource, std::string fragmentSource);
	engine_shader(std::string vertexSource, std::string geometrySource, std::string fragmentShader);
    ~engine_shader();

    engine_shader& operator=(engine_shader const &engine_shaderACopier);

    bool load();
    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    GLuint getProgramID() const;

	SHADER_TYPE getShaderType() const;

    private:

    GLuint m_vertexID;
    GLuint m_fragmentID;
	GLuint m_geometryID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
	std::string m_geometrySource;
	SHADER_TYPE m_shaderType;
};
