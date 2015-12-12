#include "engine_window.h"


engine_window::engine_window(int width, int height,std::string title) : 
	m_window_title(title), m_window_width(width), m_window_height(height), 
	m_mainwindow(0), m_glcontext(0)
{
}


engine_window::~engine_window()
{
	SDL_GL_DeleteContext(m_glcontext);
	SDL_DestroyWindow(m_mainwindow);
	SDL_Quit();
}

bool engine_window::init(){
//SDL INITALIZATION
	if (SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout << "ERROR : An error was occured while SDL initialization : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	//OPENGL VERSION
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	

	//DOUBLE BUFFER
	/*SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);*/

	//WINDOW CREATION
	m_mainwindow = SDL_CreateWindow(m_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	//DebugClass::addIf();
	if (m_mainwindow==0){

		std::cout << "ERROR : An error was occured while the window creation" << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	//SDL_EnableUno

	//OpenGL Context CREATION
	m_glcontext = SDL_GL_CreateContext(m_mainwindow);
	//DebugClass::addIf();
	if (m_glcontext==0){
		std::cout << SDL_GetError() << std::endl;
		//std::cout << "Error while creating context" << std::endl;
		SDL_DestroyWindow(m_mainwindow);
		SDL_Quit();
	
		return false;
	}
	return true;


}

bool engine_window::init_gl(){
	#ifdef WIN32
	glewExperimental=GL_TRUE;
	std::cout << std::to_string(glewExperimental) << std::endl;
		GLenum glew_initialization(glewInit());
		if (glew_initialization!=GLEW_OK){
			//ERROR MESSAGE DISPLAY
			std::cout << "ERROR : An error was occured while the glew initialization" /*<< glewGetErrorString(glew_initialization)*/ << std::endl;
			//SDL ENDING
			SDL_GL_DeleteContext(m_glcontext);
			SDL_DestroyWindow(m_mainwindow);
			SDL_Quit();

			return false;
		}
	#endif
}

void engine_window::updateResize(){
	//int a = 0;
	SDL_GetWindowSize(m_mainwindow, &m_window_width, &m_window_height);
	printf("Window Size is %ix%i\n", m_window_width, m_window_height);
}

void engine_window::update(){
	/*if (Input::input.windowResized()){
		printf("Window Resized\n");

	}*/
	SDL_GL_SwapWindow(m_mainwindow);
}

int engine_window::getWidth() const{
	return m_window_width;
}

int engine_window::getHeight() const{
	return m_window_height;
}