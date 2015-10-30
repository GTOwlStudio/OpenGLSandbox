#include "gui_Menu.h"


gui_Menu::gui_Menu(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth, float txoffset, float tyoffset) :
	m_button(name, font, x,y,w,h,depth,1.0,1.0,1.0,1.0, txoffset, tyoffset), m_actions(), m_isUnfold(false)
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
	for (int i =0;i<m_actions.size();i++){
		m_actions[i]->load();
	}
}

void gui_Menu::update(){
	m_button.update();
	m_isUnfold = m_button.isPressed();
	if (m_isUnfold){
		for (int i =0;i<m_actions.size();i++){
			m_actions[i]->update();
		}
	}
}

void gui_Menu::render(glm::mat4 &projection, glm::mat4 &modelview){
	m_button.render(projection, modelview);
	if (m_isUnfold){
	for (int i =0;i<m_actions.size();i++){
		m_actions[i]->render(projection, modelview);
	}
	}
}

gui_Button* gui_Menu::getButton(){
	return &m_button;
}

void gui_Menu::addAction(std::string name){
	printf("size=%i\n", m_actions.size());
	if (m_actions.size()!=0){
		float tw = std::max(m_button.getLabel()->getFont()->getATextWidth(name), m_actions.back()->getButton()->getWidth());
		m_actions.push_back(new gui_Action(name, *m_button.getLabel()->getFont(),m_button.getX(), m_actions.back()->getButton()->getY()-m_button.getLabel()->getFont()->getATextHeight(name),tw, m_button.getLabel()->getFont()->getATextHeight(name),  m_button.getDepth()));
		if (m_button.getLabel()->getFont()->getATextWidth(name)==tw){
		for (int i=0;i<m_actions.size()-1;i++){
			
			}
		}
		return;
	}
	m_actions.push_back(new gui_Action(name, *m_button.getLabel()->getFont(), m_button.getX(), m_button.getY()-m_button.getLabel()->getFont()->getATextHeight(name), m_button.getLabel()->getFont()->getATextWidth(name), m_button.getLabel()->getFont()->getATextHeight(name), m_button.getDepth()));
	//m_actions.back()->move();
	//m_actions.push_back(new gui_Action("Action 1", *m_button.getLabel()->getFont(), 0.0, 570.0,45.0,10.0,0.1));
	///printf("m_button.getY()=%f", m_button.getY());
	printf("size=%i\n", m_actions.size());
	
}

void gui_Menu::setPosition(float x, float y){

}

bool gui_Menu::isUnfold() const{
	return m_isUnfold;
}