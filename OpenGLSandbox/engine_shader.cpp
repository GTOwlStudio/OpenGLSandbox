#include "engine_shader.h"

// Constructeurs et Destructeur

engine_shader::engine_shader() : m_vertexID(0), m_fragmentID(0), m_geometryID(0), m_programID(0), m_vertexSource(), m_fragmentSource(), m_geometrySource(),
	m_shaderType(SHADER_VERTEX_FRAGMENT)
{
}


engine_shader::engine_shader(engine_shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;
	m_geometrySource = shaderACopier.m_geometrySource;

    // Chargement du nouveau shader

    load();
}


engine_shader::engine_shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_geometryID(0), m_programID(0),
	m_vertexSource(vertexSource), m_fragmentSource(fragmentSource), m_geometrySource(), m_shaderType(SHADER_VERTEX_FRAGMENT)
{
}

engine_shader::engine_shader(std::string vertexSource, std::string fragmentSource, std::string geometryShader) : m_vertexID(0), m_fragmentID(0), m_geometryID(0), m_programID(0),
	m_vertexSource(vertexSource), m_fragmentSource(fragmentSource), m_geometrySource(geometryShader), m_shaderType(SHADER_VERTEX_GEOMETRY_FRAGMENT)
{
}


engine_shader::~engine_shader()
{
    // Destruction du shader
	glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
	if (m_shaderType==SHADER_VERTEX_GEOMETRY_FRAGMENT){
		glDeleteShader(m_geometryID);
	}
    glDeleteProgram(m_programID);
}

// Méthodes

engine_shader& engine_shader::operator=(engine_shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;
	m_geometrySource = shaderACopier.m_geometrySource;


    // Chargement du nouveau shader

    load();


    // Retour du pointeur this

    return *this;
}


bool engine_shader::load()
{
    // Destruction d'un éventuel ancien Shader

    if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

	if (m_shaderType==SHADER_VERTEX_GEOMETRY_FRAGMENT){
		if(glIsShader(m_geometryID) == GL_TRUE){
			glDeleteShader(m_geometryID);
		}
	}

    if(glIsProgram(m_programID) == GL_TRUE){
        glDeleteProgram(m_programID);
	}


    // Compilation des shaders

    if(!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource)){
        return false;
	}

	if (m_shaderType==SHADER_VERTEX_GEOMETRY_FRAGMENT){
		if (!compilerShader(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource)){
			return false;
		}
	}
    if(!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource)){
        return false;
	}

	

    // Création du programme

    m_programID = glCreateProgram();


    // Association des shaders

    glAttachShader(m_programID, m_vertexID);
	if (m_shaderType==SHADER_VERTEX_GEOMETRY_FRAGMENT){
		glAttachShader(m_programID, m_geometryID);
	}
    glAttachShader(m_programID, m_fragmentID);


    // Verrouillage des entrées shader

    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");


    // Linkage du programme

    glLinkProgram(m_programID);


    // Vérification du linkage

    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);


    // S'il y a eu une erreur

    if(erreurLink != GL_TRUE)
    {
        // Récupération de la taille de l'erreur

        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de mémoire

        char *erreur = new char[tailleErreur + 1];


        // Récupération de l'erreur

        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        std::cout << erreur << std::endl;


        // Libération de la mémoire et retour du booléen false

        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    }



    // Sinon c'est que tout s'est bien passé

    else
        return true;
}


bool engine_shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader

    shader = glCreateShader(type);


    // Vérification du shader

    if(shader == 0)
    {
       // std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
		Util::error("ERROR : shader type (%s) n'existe pas\n");
		return false;
    }


    // Flux de lecture

    std::ifstream fichier(fichierSource.c_str());


    // Test d'ouverture

    if(!fichier)
    {
        //std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
		Util::error("ERROR : file %s is unfindable\n");
		glDeleteShader(shader);

        return false;
    }


    // Strings permettant de lire le code source

    std::string ligne;
    std::string codeSource;


    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';


    // Fermeture du fichier

    fichier.close();


    // Récupération de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource.c_str();


    // Envoi du code source au shader

    glShaderSource(shader, 1, &chaineCodeSource, 0);


    // Compilation du shader

    glCompileShader(shader);


    // Vérification de la compilation

    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur

        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de mémoire

        char *erreur = new char[tailleErreur + 1];


        // Récupération de l'erreur

        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

       // std::cout << erreur << std::endl;
		Util::error(erreur);


        // Libération de la mémoire et retour du booléen false

        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }


    // Sinon c'est que tout s'est bien passé

    else
        return true;
}


// Getter

GLuint engine_shader::getProgramID() const
{
    return m_programID;
}

SHADER_TYPE engine_shader::getShaderType() const{
	return m_shaderType;
}
