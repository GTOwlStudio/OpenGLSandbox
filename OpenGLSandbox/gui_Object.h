#pragma once

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>

class gui_Object
{
public:
	//gui_Object();
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void render(glm::mat4 &projection, glm::mat4 &modelview) = 0;
	virtual ~gui_Object() {};
};

