#pragma once
#include "glheader.h"
#include <glm/glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"

class NURBS
{
public:
	NURBS(Mesh const& mesh);
	~NURBS();
	void load();
	void update();
	void render(glm::mat4 &matrix);
	


private:
	void generateFromMesh(Mesh const& mesh);


};

