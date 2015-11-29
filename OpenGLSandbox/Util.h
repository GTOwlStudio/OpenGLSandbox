#pragma once

#include <Windows.h>

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\core\type_vec4.hpp>

class Util
{
public:
	static glm::vec2 getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos, int screen_width, int screen_height);
	static void error(const char* format, ...);

private:
	static HANDLE m_console_err_handle;
};

