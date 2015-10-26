#pragma once

#include "gui_Object.h"
#include "gui_Button.h"
#include "QuadC.h"
#include "FontAtlas.h"

class minimum_gui
{
public:
	minimum_gui(int width, int height, FontAtlas &font);
	~minimum_gui();

	void load();
	void update();
	void render(glm::mat4 &guiMatrix);

private:
	unsigned int m_objectsSize;
	unsigned int m_NNTUObjectOffset; //No Need To Update Object Offset
	gui_Object** m_objects;
	

};

