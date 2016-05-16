#pragma once

#include <iostream>
#include <vector>

#include "engine_object.h"

class engine_scene
{
public:
	engine_scene();
	~engine_scene();
	void load(std::string file);
	void update();
	void render();
	void resize(int width, int height);

private:
	std::vector<engine_object*> m_objects;


};

