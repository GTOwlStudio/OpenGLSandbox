#include "Util.h"

glm::vec2 Util::getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos){

	glm::vec4 coords = glm::transpose(matrix) * pPos;

	printf("cx=%f, cy=%f\n", coords.x*960, coords.y*600);
	return glm::vec2(coords.x, coords.y);
}