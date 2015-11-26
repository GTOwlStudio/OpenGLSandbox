#pragma once

#include "gui_Object.h"
#include "gui_Button.h"
#include "gui_Menu.h"
#include "QuadC.h"
#include "FontAtlas.h"

class minimum_gui
{
public:
	minimum_gui(int width, int height, FontAtlas &font);
	~minimum_gui();

	void load();
	void update();
	void resize(int width, int height);
	void render(glm::mat4 &guiMatrix);
	bool isFinished() const;

private:
	gui_Menu* m_menu_file;
	FontAtlas &m_font;
	int m_width;
	int m_height;
	unsigned int m_objectsSize;
	unsigned int m_NNTUObjectOffset; //No Need To Update Object Offset
	unsigned int m_ILOO; //Independantly loaded objects offset 
	gui_Object** m_objects;
	bool m_isFinished;
	

};

