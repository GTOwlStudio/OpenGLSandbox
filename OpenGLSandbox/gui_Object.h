#pragma once

#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>

class gui_Object
{
public:
	//gui_Object();
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void setPosition(float x, float y)= 0;
	//virtual void setBounds(float w, float y) = 0;
	//virtual void updateVBO(void* datas, unsigned int bytesSize, unsigned int offset)=0;
	virtual void render(glm::mat4 &projection, glm::mat4 &modelview) = 0;
	virtual ~gui_Object() {};
};

