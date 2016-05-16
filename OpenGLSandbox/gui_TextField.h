#pragma once

#include "gui_Object.h"
#include "FontAtlas.h"
#include "gui_Label.h"
#include "engine_shader.h"
#include "QuadC.h"

class gui_TextField : gui_Object
{
public:
	gui_TextField(FontAtlas &font, float x, float y, float w, float h, float depth, std::string defaultText, float r, float g, float b, float a, float tx=1.0f, float ty=0.0f);
	~gui_TextField();

	void load();
	void update();
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setText(std::string text);
	void setPosition(float x, float y);
	void setBounds(float w, float h);
	
private:
	QuadC m_background;
	gui_Label m_text;
	int m_cursorPosition; //Unsigned Int Maybe
	float m_tx, m_ty;
	float m_x, m_y, m_w, m_h, m_depth;
	bool m_isEntered;
	bool m_isExited;
	bool m_isPressed;
	//bool m_beenReleased;

};

