#include "gui_TextField.h"


gui_TextField::gui_TextField(FontAtlas &font, float x, float y, float w, float h, float depth, std::string defaultText, float r, float g, float b, float a, float tx, float ty) :
	m_x(x), m_y(y), m_w(w), m_h(h), m_text(defaultText, font, glm::vec4(x + tx, y + ty + w / 2 - font.getFontHeight() / 2, w, h), depth, r, g, b),
	m_background(x, y, w, h, depth, r, g, b, a),
	m_isEntered(false), m_isExited(true), m_isPressed(false),
	m_cursorPosition(0)
{

}

gui_TextField::~gui_TextField()
{
}

void gui_TextField::load()
{
	m_background.load();
	m_text.load();
}

void gui_TextField::update() {

}

void gui_TextField::render(glm::mat4 &projection, glm::mat4 &modelview)
{
	m_background.render(modelview, projection);
	m_text.render(modelview, projection);
}

void gui_TextField::setText(std::string text)
{
}

void gui_TextField::setPosition(float x, float y)
{
}

void gui_TextField::setBounds(float w, float h)
{
}

