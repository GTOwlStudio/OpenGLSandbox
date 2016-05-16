#include "engine_scene.h"



engine_scene::engine_scene()
{
}


engine_scene::~engine_scene()
{
	for (int i = 0; i < m_objects.size();i++) {
		delete m_objects[i];
		m_objects[i] = 0;
	}
}
