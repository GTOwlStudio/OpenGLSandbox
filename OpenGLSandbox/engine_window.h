#pragma once

#include <iostream>
#include <string>
#include <SDL2\SDL.h>

#ifdef WIN32
#include <GL/glew.h>
// Include Mac
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#include <CoreFoundation/CoreFoundation.h>
// Include UNIX/Linux
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

class engine_window
{
public:
	engine_window(int width, int height, std::string title);
	~engine_window();
	bool init();
	bool init_gl();
	void update();
	int getWidth() const;
	int getHeight() const;

private:
	SDL_Window *m_mainwindow;
	SDL_GLContext m_glcontext;

	std::string m_window_title;
	int m_window_width;
	int m_window_height;
};

