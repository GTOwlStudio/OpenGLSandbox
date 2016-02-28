#pragma once
#include "Input.h"
class gui_zone
{
public:
	gui_zone(float x, float y, float w, float h, float depth, Input &iObject);
	~gui_zone();
	float getX();
	float getY();
	float getW();
	float getH();
	float getDepth();
	void update();
	bool isEntered();
	bool isExited();

private:
	float m_coords[5];
	Input &m_input;
	bool m_isEntered;

};

