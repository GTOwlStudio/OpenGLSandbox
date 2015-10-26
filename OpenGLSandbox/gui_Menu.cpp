#include "gui_Menu.h"


gui_Menu::gui_Menu(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth) : m_button(name, font, x,y,w,h,depth,1.0,1.0,1.0,1.0)//, m_actions()
{
	
}


gui_Menu::~gui_Menu()
{
}

void gui_Menu::load(){
	m_button.load();
}

void gui_Menu::update(){
	m_button.update();
}

void gui_Menu::render(glm::mat4 &projection, glm::mat4 &modelview){
	m_button.render(projection, modelview);
}