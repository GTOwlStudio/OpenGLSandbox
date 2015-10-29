#pragma once

#include <vector>

#include "gui_Object.h"
#include "gui_Button.h"
#include "gui_Action.h"

class gui_Menu : public gui_Object
{
public:
	gui_Menu(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth, float txoffset=0.0f, float tyoffset=0.0f);
	~gui_Menu();
	void load();
	void update();
	void setPosition(float x, float y);
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	gui_Button* getButton();
	//void getLast();
	void addAction(gui_Action *action);
//	void addActions(std::string name, );

private:
	gui_Button m_button;
	std::vector<gui_Action*> m_actions;
	
};

