#pragma once

// Include Windows

#ifdef WIN32
#include <GL/glew.h>
#include <SDL2/SDL_image.h>


// Include Mac

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#include <SDL2_image/SDL_image.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <SDL2/SDL_image.h>

#endif


// Autres includes

#include <SDL2/SDL.h>
#include <iostream>
#include <string>


// Classe engine_textures

class engine_texture
{
    public:

    engine_texture();
    engine_texture(engine_texture const &textureACopier);
    engine_texture(std::string fichierImage);
	engine_texture(GLuint id);
    ~engine_texture();

    engine_texture& operator=(engine_texture const &textureACopier);
    bool load();
    SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);


    private:

    GLuint m_id;
    std::string m_fichierImage;
};