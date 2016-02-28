#include "gui_Button.h"


gui_Button::gui_Button(std::string text, FontAtlas &font, float x, float y, float w, float h, float depth, float r, float g, float b, float a, float txoffset, float tyoffset) :
	/*m_background(x,y,font.getTextWidth(text),font.getTextHeight(text),depth,r,g,b,a), m_text(text, font, glm::vec4(x,y,w,h), depth, 1.0,1.0,1.0),
	m_x(x), m_y(y), m_w(w), m_h(h), m_isEntered(false), m_isExited(true), m_isPressed(false), m_beenReleased(false)*/
	m_x(x), m_y(y), m_w(w), m_h(h), m_depth(depth),
	m_background(x, y, w, h, depth, r, g, b, a), m_text(text, font, glm::vec4(x + txoffset, y + tyoffset, w, h), depth, 0.0, 0.0, 0.0),
	m_isEntered(false), m_isExited(true), m_isPressed(false), m_beenReleased(false), m_tx(txoffset), m_ty(tyoffset), m_layout(LABEL_POS_CENTERED)
{
	//Util::green("xo%f xy%f\n", txoffset, tyoffset);
	for (int i=0;i<24;i+=4){
		m_colors[i] = r;
		m_colors[i+1] = g;
		m_colors[i+2] = b;
		m_colors[i+3] = a;
	}

	for (int i=0;i<24;i+=4){
		m_ocolors[i] = 9*r/10;
		m_ocolors[i+1] = 9*g/10;
		m_ocolors[i+2] = 9*b/10;
		m_ocolors[i+3] = a;
	}

	for (int i=0;i<24;i+=4){
		m_pcolors[i] = 8*r/10;
		m_pcolors[i+1] = 8*g/10;
		m_pcolors[i+2] = 8*b/10;
		m_pcolors[i+3] = a;
	}

	/*for (int i=0;i<24;i+=4){
		m_scolors[i] = 0.7;
		m_scolors[i+1] = 0.0;
		m_scolors[i+2] = 0.0;
		m_scolors[i+3] = 1.0;
	}*/

}

gui_Button::gui_Button(std::string text, FontAtlas & font, float x, float y, float w, float h, float depth, float r, float g, float b, float a, LABEL_POS_MODE xmode, LABEL_POS_MODE ymode) : 
	gui_Button(text, font, x, y, w, h, depth, r, g, b, a, 0.0, 0.0)
{
	if (xmode==LABEL_POS_CENTERED) {
		m_text.move((int)( (w/2) - (font.getATextWidth(text)/2) ), 0.0);
		m_tx = (int)((w / 2) - (font.getATextWidth(text) / 2));
	}
	if (ymode==LABEL_POS_CENTERED) {
		m_text.move(0.0, (int)((h / 2) - (font.getATextHeight(text) / 2)));
		m_ty = (int)((h / 2) - (font.getATextHeight(text) / 2));
	}
}




gui_Button::~gui_Button()
{
}

void gui_Button::load(){
	m_background.load();
	m_text.load();
}

void gui_Button::update(){
	//WARNING 600-my -> to dynamic value  (600-width)
	int x = Input::input.getX();
	int y = Input::input.getY_screen();//-Input::input.getY();
	//printf("x=%i y=%i\n", x,y);
	
	if (m_beenReleased){
		m_isPressed = false;
		m_beenReleased = false;
	}
	//printf("isEntered=%i\n", m_isPressed);
	if (!m_isEntered && (x>=m_x && y>=(m_y)) && ( x<(m_x+m_w) ) && (y<m_y+m_h) ){ //Mouse over
		//printf("Entered\n");
		m_isEntered = true;
		m_isExited = false;
		m_background.updateVBO(m_ocolors, sizeof(float)*24, sizeof(float)*18);
	}

	//if (!m_isExited &&  (x<m_x) || (y<m_y) || (x>(m_x+m_w)) || (y>(m_y+m_h)) ){
	if ((!m_isExited || m_isPressed) &&  !( (x>=m_x && y>=(m_y)) && ( x<(m_x+m_w) ) && (y<m_y+m_h) ) ){
		//printf("Exited\n");
		m_isExited = true;
		m_isEntered = false;
		m_isPressed = false;
		m_background.updateVBO(m_colors, sizeof(float)*24, sizeof(float)*18);
	}

	if (m_isEntered && !m_isPressed && Input::input.getMouseButton(1)){ //Pressed
		//printf("Pressed\n");
		m_isPressed = true;
		m_background.updateVBO(m_pcolors, sizeof(float)*24, sizeof(float)*18);
	}

	if (m_isPressed && m_isEntered && !Input::input.getMouseButton(1)){ // Released
		//printf("Released\n");
		m_beenReleased = true;
		m_background.updateVBO(m_colors, sizeof(float)*24, sizeof(float)*18);
	}

}

void gui_Button::updateLogic(){
	int x = Input::input.getX();
	int y = Input::input.getY_screen();//600-Input::input.getY();
	//printf("x=%i y=%i\n", x,y);
	
	if (m_beenReleased){
		m_isPressed = false;
		m_beenReleased = false;
	}
	//printf("isEntered=%i\n", m_isPressed);
	if (!m_isEntered && (x>=m_x && y>=(m_y)) && ( x<(m_x+m_w) ) && (y<m_y+m_h) ){ //Mouse over
		//printf("Entered\n");
		m_isEntered = true;
		m_isExited = false;
	}

	//if (!m_isExited &&  (x<m_x) || (y<m_y) || (x>(m_x+m_w)) || (y>(m_y+m_h)) ){
	if ((!m_isExited || m_isPressed) &&  !( (x>=m_x && y>=(m_y)) && ( x<(m_x+m_w) ) && (y<m_y+m_h) ) ){
		//printf("Exited\n");
		m_isExited = true;
		m_isEntered = false;
		m_isPressed = false;
	}

	if (m_isEntered && !m_isPressed && Input::input.getMouseButton(1)){ //Pressed
		//printf("Pressed\n");
		m_isPressed = true;
	}

	if (m_isPressed && m_isEntered && !Input::input.getMouseButton(1)){ // Released
		//printf("Released\n");
		m_beenReleased = true;
	}
}

void gui_Button::render(glm::mat4 &projection, glm::mat4 &modelview){
	m_background.render(projection, modelview);
	m_text.render(projection, modelview);
}

void gui_Button::setColor(float r, float g, float b, float a){
	
}

/*void gui_Button::moveText(float x, float y){
	
}*/

void gui_Button::setBounds(float width, float height){
	m_background.setBounds(width, height);
}

bool gui_Button::isPressed() const{
	return m_isPressed;
}


bool gui_Button::beenReleased() const{
	return m_beenReleased;
}


bool gui_Button::isEntered() const{
	return m_isEntered;
}


bool gui_Button::isExited() const{
	return m_isExited;
}

float gui_Button::getX() const{
	return m_x;
}


float gui_Button::getY() const{
	return m_y;
}


float gui_Button::getWidth() const{
	return m_w;
}


float gui_Button::getHeight() const{
	return m_h;
}

float gui_Button::getDepth() const{
	return m_depth;
}

gui_Label* gui_Button::getLabel(){
	return &m_text;
}

void gui_Button::setPosition(float x, float y){
	m_x = x;
	m_y = y;
	m_background.setPosition(x,y);
	m_text.setPosition(x+m_tx,y+m_ty);
	
}

void gui_Button::move(float relX, float relY){
	//m_background.updateVBO();
}

FontAtlas* gui_Button::getFont() const{
	return m_text.getFont();
}
