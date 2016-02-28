#include "engine_camera.h"


engine_camera::engine_camera(float const & fov, float const & ratio, float const & n, float const & f) : m_projection(glm::perspective(fov,ratio,n,f)), m_view(1.0f), m_mng()
{
	m_VP = m_projection * m_view;
	m_mng.addValueSpy(Input::input.getMouseButtonRef(2));
}

engine_camera::engine_camera(float left, float right, float bottom, float top, float n, float f) : m_projection(glm::ortho(left, right, bottom, top, n, f)), m_view(1.0f), m_mng()
{
	
	m_VP = m_projection * m_view;
	m_mng.addValueSpy(Input::input.getMouseButtonRef(2));
}


void engine_camera::lookAt(glm::vec3 pos, glm::vec3 center, glm::vec3 axis)
{
	m_view = glm::lookAt(pos,center,axis);
	m_VP = m_projection * m_view;
}

void engine_camera::resize(int w, int h)
{
	m_projection = glm::perspective(60.0f, (float)w/h,0.1f,100.0f);
	m_VP = m_projection * m_view;
}

void engine_camera::update()
{
	//printf("Update");
	m_mng.updateEvent();
	if (m_mng.isEvent()) {
		while (m_mng.isEvent()) {
			if (m_mng.readEventId()==0) {
				m_controller.m_MMB = m_mng.getValue(0);
			}
		}
		
	}
	if (m_controller.m_MMB&&Input::input.mouseIsMoving()) {
			rotate(Input::input.getX(), glm::vec3(0, 1, 1)); //X
		
		//rotate(glm::asin((unsigned int)Input::input.getYRel()), glm::vec3(0,1,0));
	}

}

engine_camera::~engine_camera()
{
}

void engine_camera::rotate(float angle, glm::vec3 axis)
{
	m_VP = m_projection * glm::rotate(m_view, angle, axis);
}

glm::mat4 engine_camera::getMatrix() const
{
	return m_VP;
}

