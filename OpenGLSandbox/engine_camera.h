#pragma once

#include <glm/glm.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"
#include "EventManager.h"
#include "MathUtil.h"

enum CAMERA_TYPE {

};

struct camera_controller_struct {

	bool m_MMB = false;
	

};

class engine_camera
{
public:
	engine_camera(float const& fov, float const& ratio, float const& n, float const& f);
	engine_camera(float left, float right, float bottom, float top, float n, float f);
	void lookAt(glm::vec3 pos, glm::vec3 center, glm::vec3 axis);
	void resize(int w, int h);
	void update();
	~engine_camera();
	void setRotation(float angle, glm::vec3 axis);
	void rotate(float dAngle, glm::vec3 axis);
	void rotationAtp(float angle, glm::vec3 atp);
	glm::mat4 getMatrix() const;
	glm::mat4 getWorldMatrix() const;

private:
	glm::mat4 m_VP; //View Projection matrix
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_phi;
	float m_teheta;

	glm::vec3 m_rotation;
	glm::vec3 m_atp; //Alpha Theta Phi
	float m_angle;

	glm::vec3 m_lateralAxis;
	glm::vec3 m_verticalAxis;

	glm::vec3 m_position;
	glm::vec3 m_cible;

	EventManager m_mng;
	camera_controller_struct m_controller;

};

