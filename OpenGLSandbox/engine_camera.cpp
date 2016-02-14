#include "engine_camera.h"


engine_camera::engine_camera(glm::vec3 position, glm::vec3 cible, glm::vec3 verticalAxis) :
	m_position(position), m_cible(cible), m_verticalAxis(verticalAxis)
{

}

engine_camera::engine_camera(float const & fov, float const & ratio, float const & near, float const & far) : m_projection(glm::perspective(fov,ratio,near,far)), m_view(1.0f)
{
	m_VP = m_projection * m_view;
}


void engine_camera::lookAt(glm::vec3 pos, glm::vec3 center, glm::vec3 axis)
{
	m_view = glm::lookAt(pos,center,axis);
	m_VP = m_projection * m_view;
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

