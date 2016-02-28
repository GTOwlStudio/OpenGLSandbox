#include "gui_zone.h"

gui_zone::gui_zone(float x, float y, float w, float h, float depth, Input &iObject) : m_input(iObject), m_isEntered(false)
{
	m_coords[0] = x;
	m_coords[1] = y;
	m_coords[2] = w;
	m_coords[3] = h;
	m_coords[4] = depth;
	printf("x:%f y:%f x1:%f x2:%f\n",  x,y,w+x,h+y);
}

gui_zone::~gui_zone()
{
}

float gui_zone::getX()
{
	return m_coords[0];
}

float gui_zone::getY()
{
	return m_coords[1];
}

float gui_zone::getW()
{
	return m_coords[2];
}

float gui_zone::getH()
{
	return m_coords[3];
}

float gui_zone::getDepth()
{
	return m_coords[4];
}

void gui_zone::update() {
	int x = m_input.getX();
	int y = m_input.getY_screen();
	if (x >= m_coords[0] && y >= m_coords[1] && x <= (m_coords[0] + m_coords[2]) && y <= (m_coords[1] + m_coords[3])) {
		if (!m_isEntered) {
			m_isEntered = true;
			return;
		}
	}
	if (m_isEntered) {
		m_isEntered = false;
	}
}

bool gui_zone::isEntered() {

	return m_isEntered;

}

bool gui_zone::isExited()
{
	return !m_isEntered;
}
