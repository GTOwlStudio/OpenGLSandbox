#include "Util.h"

glm::vec2 Util::getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos, int screen_width, int screen_height){

	glm::vec4 coords = glm::transpose(matrix) * pPos;

	printf("cx=%f, cy=%f\n", coords.x*screen_width, coords.y*screen_height);
	return glm::vec2(coords.x, coords.y);
}