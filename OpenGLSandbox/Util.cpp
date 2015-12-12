#include "Util.h"

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

HANDLE Util::m_console_err_handle = GetStdHandle(STD_ERROR_HANDLE);

glm::vec2 Util::getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos, int screen_width, int screen_height){

	glm::vec4 coords = glm::transpose(matrix) * pPos;

	printf("cx=%f, cy=%f\n", coords.x*screen_width, coords.y*screen_height);
	return glm::vec2(coords.x, coords.y);
}



void Util::error(const char *format, ...){
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_RED|FOREGROUND_INTENSITY);
	va_list args;
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
}

void Util::dev(const char *format, ...){
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	va_list args;
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
}