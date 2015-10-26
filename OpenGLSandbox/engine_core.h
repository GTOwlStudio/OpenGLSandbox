#pragma once

#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\core\type_mat4x4.hpp>

#include "engine_window.h"
#include "Input.h"
#include "Quad.h"
#include "FontAtlas.h"
#include "gui_Label.h"
#include "gui_Button.h"
#include "QuadC.h"
#include "minimum_gui.h"
#include "gui_devtest.h"

class engine_core
{
public:
	engine_core(int w, int h, std::string mainwindowtitle, int fpsCap);
	~engine_core();
	bool init();
	void mainLoop();

private:
	engine_window *m_mainwindow;
	//Input m_input;
	unsigned int m_fpsCap;
	unsigned int m_timeBetweenFrames;
	Uint32 m_while_start, m_while_duration;
};

