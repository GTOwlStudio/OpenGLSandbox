#include "gui_Menu.h"


gui_Menu::gui_Menu(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth, float txoffset, float tyoffset) :
	m_button(name, font, x,y,w,h,depth,1.0,1.0,1.0,1.0, txoffset, tyoffset), m_actions(), m_isUnfold(false), m_isEntered(false), m_isExited(true), m_lastActionID(-1)
{
	
}

gui_Menu::gui_Menu(std::string name, FontAtlas & font, float x, float y, float w, float h, float depth, LABEL_POS_MODE xmode, LABEL_POS_MODE ymode) : 
	m_button(name, font, x, y, w, h, depth, 1.0, 1.0, 1.0, 1.0, xmode, ymode), m_actions(), m_isUnfold(false), m_isEntered(false), m_isExited(true), m_lastActionID(-1)
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
	/*for (int i =0;i<m_actions.size();i++){
		m_actions[i]->load();
	}*/
}

void gui_Menu::update(){
	/*m_button.update();
	m_isUnfold = m_button.beenReleased();
	if (m_isUnfold){
		for (int i =0;i<m_actions.size();i++){
			m_actions[i]->update();
		}
	m_isEntered = false;
	for (int i =0;i<m_actions.size();i++){
		if (m_actions[i]->getButton()->isEntered()){
				m_isEntered=true;
				m_isExited=false;
				break;
			}
		}
	}*/
	/*if (m_isUnfold!=m_button.beenReleased()){
		printf("released\n");
	}*/
	if (m_lastActionID!=-1){
		m_lastActionID = -1;
	}
	if (!m_isUnfold){
		m_isUnfold=m_button.beenReleased();
		m_button.update();
	}
	if (m_isUnfold){
		m_button.updateLogic();
	for (int i =0;i<m_actions.size();i++){
			m_actions[i]->update();
	}
//	m_isEntered = false; m_isExited = false; //To Modify
	for (int i =0;i<m_actions.size();i++){
		if(m_button.isEntered()){return;}
		if (m_actions[i]->getButton()->isEntered()){
				m_isEntered=true;
				m_isExited=false;
				if (m_actions[i]->getButton()->beenReleased()){
					m_isEntered=false;
					m_isExited=true; m_isUnfold = false;
					/*std::cout << m_actions[i]->getName() << " launched\n";
					printf("i=%i\n", i);*/
					m_lastActionID = i;
					//printf("%s launched\n", m_actions[i]->getName(), i);
				}
				return;
			}
		}
	m_isEntered=false; m_isExited = true;
	m_isUnfold = false;
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
		m_actions.back()->load();
		if (m_button.getLabel()->getFont()->getATextWidth(name)==tw){
		for (int i=0;i<m_actions.size()-1;i++){
			//printf("i=%i\n", i);
			m_actions[0]->getButton()->setBounds(tw, m_actions[0]->getButton()->getHeight());
			}
		}
		return;
	}
	m_actions.push_back(new gui_Action(name, *m_button.getLabel()->getFont(), m_button.getX(), m_button.getY()-m_button.getLabel()->getFont()->getATextHeight(name), m_button.getLabel()->getFont()->getATextWidth(name), m_button.getLabel()->getFont()->getATextHeight(name), m_button.getDepth()));
	m_actions.back()->load();
	//m_actions.back()->move();
	//m_actions.push_back(new gui_Action("Action 1", *m_button.getLabel()->getFont(), 0.0, 570.0,45.0,10.0,0.1));
	///printf("m_button.getY()=%f", m_button.getY());
	printf("size=%i\n", m_actions.size());
	
}

void gui_Menu::setPosition(float x, float y){
	//printf("x");
	float xb = m_button.getX();
	float yb = m_button.getY();
	float tmpX;
	float tmpY;
	for (int i = 0; i < m_actions.size();i++) {
		Util::green("x=%f y=%f\n", x - (m_actions[i]->getButton()->getX() - xb), y - (m_actions[i]->getButton()->getY() - yb));
		m_actions[i]->setPosition(x+(m_actions[i]->getButton()->getX()-xb), y+(m_actions[i]->getButton()->getY()-yb));
	}
	m_button.setPosition(x, y);
}

bool gui_Menu::isUnfold() const{
	return m_isUnfold;
}

int gui_Menu::getLastActionID() const{
	return m_lastActionID;
}