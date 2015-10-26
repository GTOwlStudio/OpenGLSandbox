#pragma once

#include "gui_Object.h"
#include "gui_Label.h"
#include  "QuadC.h"
#include "FontAtlas.h"
#include "Input.h"

class gui_Button : public gui_Object
{
public:
	gui_Button(std::string text, FontAtlas &font,float x, float y, float w, float h, float depth,  float r, float g, float b, float a=1.0f);
	~gui_Button();
	void load();
	void update();
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	bool isPressed() const;
	bool beenReleased() const;
	bool isEntered() const;
	bool isExited() const;

private:
	gui_Label m_text;
	QuadC m_background;
	float m_colors[24];
	float m_scolors[24];
	float m_x, m_y, m_w, m_h, m_depth;
	bool m_isEntered;
	bool m_isExited;
	bool m_isPressed;
	bool m_beenReleased;

};

