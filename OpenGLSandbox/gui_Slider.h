#pragma once

#include "gui_Object.h"
#include "QuadC.h"
#include "gui_Label.h"
#include "Input.h"

class gui_Slider : gui_Object
{
public:
	gui_Slider(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth, float maxValue, float defaultValue=0.0f, float minValue=0.0f);
	~gui_Slider();
	void load();
	void update();
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setValue(float value);
	void setText(std::string text);
	void setPosition(float x, float y);

	float getValue() const;
	float getMinValue() const;
	float getMaxValue() const;
	bool isExited() const;
	bool isEntered() const;
	bool isPressed() const;
	bool beenReleased() const;

private:
	float m_x, m_y, m_w, m_h;
	QuadC m_background;
	QuadC m_filler;
	gui_Label m_text;
	std::string m_format;
	float m_value;
	float m_minValue;
	float m_maxValue;
	bool m_isEntered;
	bool m_isExited;
	bool m_isPressed;
	bool m_beenReleased;
	float m_colors[24]; //Colors of the button
	float m_ocolors[24]; //Colors of the button when the mouse is over
	float m_pcolors[24]; //Colors of the button when is pressed

};

