#include "engine_texture.h"


// Constructeurs et Destructeur

engine_texture::engine_texture() : m_id(0), m_imageFile("")
{

}


engine_texture::engine_texture(engine_texture const &textureToCopy)
{
    // Copie de la texture

    m_imageFile = textureToCopy.m_imageFile;
    load();
}



engine_texture::engine_texture(std::string fichierImage) : m_id(0), m_imageFile(fichierImage)
{

}

engine_texture::engine_texture(GLuint id) : m_imageFile("Texture load from an ID"){
	if (glIsTexture(id)==GL_TRUE){
		m_id = id;;
	}
	else {
		std::printf("Requested ID %d do not exist\n", id);
		m_id = 0;
	}
}

engine_texture::~engine_texture()
{
    // Destruction de la texture
    glDeleteTextures(1, &m_id);
}


// Méthodes

engine_texture& engine_texture::operator=(engine_texture const &textureToCopy)
{
    // Copie de la texture

    m_imageFile = textureToCopy.m_imageFile;
    load();


    // Retour du pointeur *this

    return *this;
}


bool engine_texture::load()
{
    // Chargement de l'image dans une surface SDL
	if (m_id!=0){
		return true;
	}
    SDL_Surface *imageSDL = IMG_Load(m_imageFile.c_str());

    if(imageSDL == 0)
    {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
		//delete imageSDL;
        return false;
    }


    // Inversion de l'image

    SDL_Surface *reversedImage = reversePixels(imageSDL);
    SDL_FreeSurface(imageSDL);


    // Destruction d'une éventuelle ancienne texture

    if(glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);


    // Génération de l'ID

    glGenTextures(1, &m_id);


    // Verrouillage

    glBindTexture(GL_TEXTURE_2D, m_id);


    // Format de l'image

    GLenum internalFormat(0);
    GLenum format(0);


    // Détermination du format et du format interne pour les images à 3 composantes

    if(reversedImage->format->BytesPerPixel == 3)
    {
        // Format interne

        internalFormat = GL_RGB;


        // Format

        if(reversedImage->format->Rmask == 0xff)
            format = GL_RGB;

        else
            format = GL_BGR;
    }


    // Détermination du format et du format interne pour les images à 4 composantes

    else if(reversedImage->format->BytesPerPixel == 4)
    {
        // Format interne

        internalFormat = GL_RGBA;


        // Format

        if(reversedImage->format->Rmask == 0xff)
            format = GL_RGBA;

        else
            format = GL_BGRA;
    }


    // Dans les autres cas, on arrête le chargement

    else
    {
        std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
        SDL_FreeSurface(reversedImage);

        return false;
    }


    // Copie des pixels

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, reversedImage->w, reversedImage->h, 0, format, GL_UNSIGNED_BYTE, reversedImage->pixels);


    // Application des filtres

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    // Déverrouillage

    glBindTexture(GL_TEXTURE_2D, 0);


    // Fin de la méthode

    SDL_FreeSurface(reversedImage);
    return true;
}


SDL_Surface* engine_texture::reversePixels(SDL_Surface *imageSource) const
{
    // Copie conforme de l'image source sans les pixels

    SDL_Surface *reversedImage = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
                                                         imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


    // Tableau intermédiaires permettant de manipuler les pixels

    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) reversedImage->pixels;


    // Inversion des pixels

    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }


    // Retour de l'image inversée

    return reversedImage;
}




GLuint engine_texture::getID() const
{
    return m_id;
}


void engine_texture::setImageFile(const std::string &fichierImage)
{
    m_imageFile = fichierImage;
}

