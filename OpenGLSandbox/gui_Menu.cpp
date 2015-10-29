#include "gui_Menu.h"


gui_Menu::gui_Menu(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth) : m_button(name, font, x,y,w,h,depth,1.0,1.0,1.0,1.0)//, m_actions()
{
	
}


gui_Menu::~gui_Menu()
{
	for (int i =0;i<m_actions.size();i++){
		delete m_actions[i];
		m_actions[i]=0;
	}
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

gui_Button* gui_Menu::getButton(){
	return &m_button;
}

void gui_Menu::addAction(gui_Action *action){
	if (m_actions.size()!=0){
		m_actions.push_back(action);
		return;
	}
	m_actions.push_back(action);
	//m_actions.back()->move();
	
}

void gui_Menu::setPosition(float x, float y){

}