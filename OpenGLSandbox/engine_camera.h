#pragma once

#include <glm/glm.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CAMERA_TYPE {

};

class engine_camera
{
public:
	engine_camera(glm::vec3 position, glm::vec3 cible, glm::vec3 verticalAxis);
	engine_camera( float const& fov, float const& ratio, float const& near, float const& far);
	engine_camera(float left, float right, float bottom, float top, float near, float var);
	void lookAt(glm::vec3 pos, glm::vec3 center, glm::vec3 axis);
	~engine_camera();
	void rotate(float angle, glm::vec3 axis);
	glm::mat4 getMatrix() const;

private:
	glm::mat4 m_VP; //View Projection matrix
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_phi;
	float m_teheta;

	glm::vec3 m_lateralAxis;
	glm::vec3 m_verticalAxis;

	glm::vec3 m_position;
	glm::vec3 m_cible;

};

