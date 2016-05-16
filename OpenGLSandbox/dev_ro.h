#pragma once
#include "engine_shader.h"

class dev_ro
{
public:
	dev_ro(float x, float y, float w, float h);
	~dev_ro();
	void load();
	void render();

private:
	float m_quads[12];
	float m_coords[8];
	float m_colors[12];
	unsigned int m_indices[6];
	engine_shader m_shaderInit;
};

