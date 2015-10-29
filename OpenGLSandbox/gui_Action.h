#pragma once

#include "gui_Object.h"
#include "gui_Button.h"

class gui_Action : public gui_Object
{
public:
	gui_Action(std::string name);
	~gui_Action();
	void load();
	void update();
	void setPosition(float x, float y);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
private:


};

