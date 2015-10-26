#include "minimum_gui.h"


minimum_gui::minimum_gui(int width, int height, FontAtlas &font) : m_objectsSize(2), m_NNTUObjectOffset(1)
{
	m_objects = new gui_Object*[m_objectsSize];
	m_objects[0] = new QuadC(0.0, height-20.0, width, 20.0, 0.700, 1.0, 1.0, 1.0, 1.0);
	m_objects[1] = new gui_Button("File", font, 0.0, height-20.0, 20.0, 20.0, 0.701, 0.0, 1.0, 1.0, 1.0);
	
	//m_objects[0] = new QuadC(100.0, 150.0, 100.0, 50.0, 0.7, 1.0, 1.0, 0.0, 1.0);
}

void minimum_gui::load(){
	for (int i =0;i<m_objectsSize;i++){
		//printf("i=%i\n", i);
		m_objects[i]->load();
	}
}

void minimum_gui::update(){
	for (int i =m_NNTUObjectOffset;i<m_objectsSize;i++){
		m_objects[i]->update();
		//printf("i=%i\n", i);
	}
}

void minimum_gui::render(glm::mat4 &guiMatrix){
	/*for (int i =0;i<m_objectsSize;i++){
		m_objects[i]->render(guiMatrix, glm::mat4(1.0));
	}*/

	m_objects[0]->render(guiMatrix, glm::mat4(1.0));
	m_objects[1]->render(guiMatrix, glm::mat4(1.0));

}

minimum_gui::~minimum_gui()
{
	for (int i = 0;i<m_objectsSize;i++){
		delete m_objects[i]; m_objects[i] = 0;
	}
	delete[] m_objects; m_objects = 0;
}
