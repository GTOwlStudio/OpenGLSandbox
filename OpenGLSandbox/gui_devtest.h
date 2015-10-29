#pragma once

#include "gui_Object.h"
#include "QuadC.h"
#include "FontAtlas.h"

class gui_devtest : public gui_Object
{
public:
	gui_devtest(std::string text, FontAtlas &font);
	~gui_devtest();
	void load();
	void update();
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	void setPosition(float x, float y);
private:
	std::string m_text;
	FontAtlas *m_fontAtlas;
};

