#include "gui_devtest.h"


gui_devtest::gui_devtest(std::string text, FontAtlas &font) : m_fontAtlas(&font), m_text(text)
{

}


gui_devtest::~gui_devtest()
{
	m_fontAtlas = 0;
}

void gui_devtest::load(){
}

void gui_devtest::update(){
	printf("w:%f\n", m_fontAtlas->getATextWidth(m_text));
	printf("h:%f\n", m_fontAtlas->getATextHeight(m_text));
}

void gui_devtest::render(glm::mat4 &projection, glm::mat4 &modelview){

}