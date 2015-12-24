#include "gui_Slider.h"



gui_Slider::gui_Slider(std::string name, FontAtlas &font, float x, float y, float w, float h, float depth, float maxValue, float defaultValue, float minValue) :
	m_background(x, y, w, h, depth, 1.0f, 1.0f, 1.0f, 1.0f), m_filler(x + 1.0f, y + 1.0f, w - (w*(defaultValue / maxValue)) - 2.0f, h - 2.0f, depth, 0.0f, 200.0f / 255.0f, 245.0f / 255.0f, 1.0f),
	m_maxValue(maxValue), m_minValue(minValue), m_value(defaultValue),
	m_text(name, font, glm::vec4((int)(x + (w / 2) - font.getATextWidth(name) / 2), (int)(y + (h / 2) - font.getATextHeight(name) / 2), font.getATextWidth(name), font.getATextHeight(name)), depth, 0.0f, 0.0f, 0.0f),
	m_x(x), m_y(y), m_w(w), m_h(h),
	m_isEntered(false), m_isExited(true), m_isPressed(false), m_beenReleased(false), m_format(name)
{
	for (int i = 0; i < 24;i+=4) {
		m_colors[i] = 1.0;
		m_colors[i+1] = 1.0;
		m_colors[i+2] = 1.0;
		m_colors[i+3] = 1.0;

		m_ocolors[i] = 0.85;
		m_ocolors[i + 1] = 0.85;
		m_ocolors[i + 2] = 0.85;
		m_ocolors[i + 3] = 1.0;

		m_pcolors[i] = 0.75;
		m_pcolors[i + 1] = 0.75;
		m_pcolors[i + 2] = 0.75;
		m_pcolors[i + 3] = 1.0;

	}
}


gui_Slider::~gui_Slider()
{
	
}

void gui_Slider::load() {
	m_background.load();
	m_filler.load();
	m_text.load();
}

void gui_Slider::update() {
	int x = Input::input.getX();
	int y = Input::input.getY_screen();//-Input::input.getY();
									   //printf("x=%i y=%i\n", x,y);

	if (m_beenReleased) {
		m_isPressed = false;
		m_beenReleased = false;
	}
	//printf("isEntered=%i\n", m_isPressed);
	if (!m_isEntered && (x >= m_x && y >= (m_y)) && (x<(m_x + m_w)) && (y<m_y + m_h)) { //Mouse over
																						//printf("Entered\n");
		m_isEntered = true;
		m_isExited = false;
		m_background.updateVBO(m_ocolors, sizeof(float) * 24, sizeof(float) * 18);
	}

	//if (!m_isExited &&  (x<m_x) || (y<m_y) || (x>(m_x+m_w)) || (y>(m_y+m_h)) ){
	if ((!m_isExited || m_isPressed) && !((x >= m_x && y >= (m_y)) && (x<(m_x + m_w)) && (y<m_y + m_h))) {
		//printf("Exited\n");
		m_isExited = true;
		m_isEntered = false;
		m_isPressed = false;
		m_background.updateVBO(m_colors, sizeof(float) * 24, sizeof(float) * 18);
	}

	if (m_isEntered && !m_isPressed && Input::input.getBoutonSouris(1)) { //Pressed
																		  //printf("Pressed\n");
		m_isPressed = true;
		m_background.updateVBO(m_pcolors, sizeof(float) * 24, sizeof(float) * 18);
	}

	

	if (m_isPressed && m_isEntered && !Input::input.getBoutonSouris(1)) { // Released
																		  //printf("Released\n");
		m_beenReleased = true;
		m_background.updateVBO(m_colors, sizeof(float) * 24, sizeof(float) * 18);
	}
	
	if (m_isPressed && m_isEntered) {
		//m_filler.setBounds(0, m_filler.);
		setValue((x-m_x-1.0f)/((m_w-2.0f)/m_maxValue));
		//m_filler.setBounds((m_w - 2.0f) - ((m_w - 2.0f)*((m_maxValue - (x - m_x - 0.0f) / ((m_w - 2.0f) / m_maxValue)) / m_maxValue)), m_filler.getHeight());
	}

}

void gui_Slider::render(glm::mat4 & projection, glm::mat4 & modelview)
{
	m_background.render(projection, modelview);
	m_filler.render(projection, modelview);
	m_text.render(projection, modelview);
}

void gui_Slider::setValue(float value)
{
	if (value>=m_minValue && value<=m_maxValue) {
		m_value = value;
		m_filler.setBounds((m_w-2.0f) - ((m_w-2.0f)*((m_maxValue-m_value )/ m_maxValue)), m_filler.getHeight());
		setText(m_format);
	}
	else {
		Util::conceptor("%f must be contain in [%f, %f]\n",value,m_minValue, m_maxValue);
	}
}

void gui_Slider::setText(std::string text)
{
	m_format = text;
	std::string tmp = m_format;
	//printf("here\n");
	for (int i = 0; i < m_format.size();i++) {
		if (m_format.substr(i,2)=="%v") {
			tmp.erase(i,2);
			tmp.insert(i,std::to_string(m_value));
			m_text.setText(tmp);
			break;
		}
	}
}

void gui_Slider::setPosition(float x, float y)
{
}

float gui_Slider::getValue() const
{
	return m_value;
}

float gui_Slider::getMinValue() const
{
	return m_minValue;
}

float gui_Slider::getMaxValue() const
{
	return m_maxValue;
}

bool gui_Slider::isExited() const
{
	return m_isExited;
}

bool gui_Slider::isEntered() const
{
	return m_isEntered;
}

bool gui_Slider::isPressed() const
{
	return m_isPressed;
}

bool gui_Slider::beenReleased() const
{
	return m_beenReleased;
}
