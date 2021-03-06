#pragma once

#include "gui_Object.h"
#include "gui_Label.h"
#include  "QuadC.h"
#include "FontAtlas.h"
#include "Input.h"
#include "Layout.h"

class gui_Button : public gui_Object
{
public:
	gui_Button(std::string text, FontAtlas &font,float x, float y, float w, float h, float depth,  float r, float g, float b, float a=1.0f, float txoffset=0.0f, float tyoffset=0.0f);
	gui_Button(std::string text, FontAtlas &font, float x, float y, float w, float h, float depth, float r, float g, float b, float a,LABEL_POS_MODE xmode, LABEL_POS_MODE ymode);
	~gui_Button();
	void load();
	void update(); //Update Logic and Data
	void updateLogic(); //Update Logic
	void render(glm::mat4 &projection, glm::mat4 &modelview);
	/*void setTextRelPosition(float x, float y); //Set a position on the button x=0 is the bottom and y=0 the right
	void moveText(float x, float y); //Move the button*/
	void setColor(float r, float g, float b, float a=1.0f);
	//void setOverColor(float r, float g, float b, float a=1.0f);
	//void setPressedColor(float r, float g, float b, float a=1.0f);
	void setPosition(float x, float y);
	void move(float relX, float relY);
	void setBounds(float w, float h);
	/*void setWidth(float w);
	void setHeight(float h);*/
	gui_Label* getLabel();
	bool isPressed() const;
	bool beenReleased() const;
	bool isEntered() const;
	bool isExited() const;
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	float getDepth() const;
	FontAtlas* getFont() const;

private:
//	void updateVBO(void* data, unsigned int bytesSize, unsigned int size);
	gui_Label m_text;
	float m_tx, m_ty; 
	QuadC m_background;
	float m_colors[24]; //Colors of the button
	float m_ocolors[24]; //Colors of the button when the mouse is over
	float m_pcolors[24]; //Colors of the button when is pressed
	float m_x, m_y, m_w, m_h, m_depth;
	bool m_isEntered;
	bool m_isExited;
	bool m_isPressed;
	bool m_beenReleased;
	LABEL_POS_MODE m_layout;

};

