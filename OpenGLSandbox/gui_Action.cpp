#include "gui_Action.h"


gui_Action::gui_Action(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth) : m_button(name, font, x,y,w,h,depth, 1.0f,1.0f,1.0f)
{
	printf("x=%f y=%f w=%f h=%f depth=%f\n",x,y,w,h, depth);
}


gui_Action::~gui_Action()
{
}

void gui_Action::load(){
	//printf("loaded\n");
	m_button.load();
}

void gui_Action::update(){
	m_button.update();
}

void gui_Action::render(glm::mat4 &projection, glm::mat4 &modelview){
	//printf("render\n");
	m_button.render(projection, modelview);
}

void gui_Action::setPosition(float x, float y){

}

gui_Button* gui_Action::getButton(){
	return &m_button;
}