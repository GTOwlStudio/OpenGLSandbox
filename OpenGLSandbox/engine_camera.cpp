#include "engine_camera.h"


engine_camera::engine_camera(float const & fov, float const & ratio, float const & n, float const & f) : m_projection(glm::perspective(fov, ratio, n, f)), m_view(1.0f), m_mng(), m_rotation(0, 0, 0), m_angle(0),m_atp(0.0f, 0.0f, 0.0f)
{
	m_VP = m_projection * m_view;
	m_mng.addValueSpy(Input::input.getMouseButtonRef(2));
}

engine_camera::engine_camera(float left, float right, float bottom, float top, float n, float f) : m_projection(glm::ortho(left, right, bottom, top, n, f)), m_view(1.0f), m_mng(), m_rotation(0,0,0), m_angle(0), m_atp(0.0f, 0.0f, 0.0f)
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
		rotationAtp(Input::input.getXRel(), glm::vec3(0.0f, 0.0f, 1.0f)); //X
		rotationAtp(Input::input.getYRel(), glm::vec3(1.0f, 0.0f, 0.0f));
		//rotationX(Input::input.getXRel());
		//rotationY(Input::input.getYRel());
		//rotate(glm::length(glm::vec2(Input::input.getXRel(), Input::input.getYRel())), glm::vec3(0, 0, 1));// glm::vec3(0, Input::input.getYRel(), Input::input.getYRel()));
			//rotate(Input::input.getYRel(), glm::vec3(0,0, 0));
			//printf("mry=%i\n", Input::input.getYRel());
		//rotate(glm::asin((unsigned int)Input::input.getYRel()), glm::vec3(0,1,0));
	}

}

engine_camera::~engine_camera()
{
}

void engine_camera::setRotation(float angle, glm::vec3 axis)
{
	m_VP = m_projection * glm::rotate(m_view, angle, axis);
	m_rotation = axis*angle;
	m_angle = angle;
}

void engine_camera::rotate(float dAngle, glm::vec3 axis) {
	//m_rotation += dAngle * axis;
	//m_angle += dAngle;
	//(dAngle<0) ? (printf("\t<")) : NULL;
	/*printf("x=%f, y=%f, z=%f n=%f\n", m_rotation.x, m_rotation.y, m_rotation.z, glm::length(m_rotation));
	//printf("axis x=%f y=%f z=%f\n", axis.x, axis.y, axis.z);
	if (glm::length(m_rotation)>360.0f) {
		if (abs(m_rotation.x)>=360.0f) {
			(m_rotation.x > 0) ? m_rotation.x -= 360.0f : m_rotation.x += 360.0f;
			printf("X %f\n", m_rotation.x);
		}
		if (abs(m_rotation.y) >= 360.0f) {
			(m_rotation.y > 0) ? m_rotation.y -= 360.0f : m_rotation.y += 360.0f;
			printf("Y %f\n", m_rotation.y);
		}
		if (abs(m_rotation.z) >= 360.0f) {
			(m_rotation.z > 0) ? m_rotation.z -= 360.0f : m_rotation.z += 360.0f;
			printf("Z %f\n", m_rotation.z);
		}
		printf("Here");
	}*/
	m_VP = m_projection * glm::rotate(m_view, dAngle, axis);

	
}

void engine_camera::rotationAtp(float angle, glm::vec3 atp)
{
	m_atp+=angle*atp;
	m_angle += angle;
	//glm::vec3 tn(glm::normalize(m_atp));
	printf("ATP x=%f y=%f z=%f\n", m_atp.x, m_atp.y, m_atp.z);
	//printf("ATPN x=%f y=%f z=%f\n", tn.x, tn.y, tn.z);
	printf("cos(%f)=%f\n", m_atp.x, glm::cos(glm::degrees(m_atp.x)));
	//m_VP = m_projection * glm::rotate(m_view, );
	glm::vec3 axis = glm::sin(glm::degrees(m_atp));
	printf("Axis x=%f y=%f z=%f\n", axis.x, axis.y, axis.z);
	m_VP = m_projection*glm::rotate(m_view, m_angle, glm::normalize(axis));// *glm::rotate(m_view, atp.y, glm::vec3(0, 1, 0))*glm::rotate(m_view, atp.z, glm::vec3(0, 0, 1));
}



glm::mat4 engine_camera::getMatrix() const
{
	return m_VP;
}

glm::mat4 engine_camera::getWorldMatrix() const {
	return m_view;
}
