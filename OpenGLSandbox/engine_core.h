#pragma once

#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <cmath>

#include "engine_window.h"
#include "Input.h"
#include "Quad.h"
#include "FontAtlas.h"
#include "gui_Label.h"
#include "gui_Button.h"
#include "QuadC.h"
#include "minimum_gui.h"
#include "gui_devtest.h"
#include "gui_Action.h"
#include "Line.h"
#include "Util.h"
#include "dev_gs.h"
#include "BSpline.h"
#include "dev_Quad.h"
#include "gui_TextField.h"
#include "gui_Slider.h"
#include "dev_Label.h"
#include "ParticleSystem.h"
#include "dev_ro.h"
#include "engine_camera.h"


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
	Uint32 m_while_start, m_while_duration, m_last_while_duration;
};

