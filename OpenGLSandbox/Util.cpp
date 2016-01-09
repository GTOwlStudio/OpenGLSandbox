#include "Util.h"

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

HANDLE Util::m_console_err_handle = GetStdHandle(STD_ERROR_HANDLE);

glm::vec2 Util::getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos, int screen_width, int screen_height){

	glm::vec4 coords = glm::transpose(matrix) * pPos;

	printf("cx=%f, cy=%f\n", coords.x*screen_width, coords.y*screen_height);
	return glm::vec2(coords.x, coords.y);
}

std::vector<float> Util::getPointerDataArrayf(int arraySize, std::vector<float> data,int argSize, ...) {
	std::vector<float> a;
	va_list ids;
	va_start(ids, argSize);
	for (int i = 0; i < argSize;i++) {
		a.push_back(data[va_arg(ids, int)]);
	}
	va_end(ids);
	return a;
}

std::vector<float> Util::getXDimensionArrayf(std::vector<float> arr, unsigned int Xn, unsigned int Xd) {
	std::vector<float> a;
	for (int i = 0; i < arr.size()/Xn;i++) {
		a.push_back(arr[Xn*i+Xd]);
	}
	return a;
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

void Util::conceptor(const char * format, ...)
{
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void Util::green(const char *format, ...) {
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	SetConsoleTextAttribute(Util::m_console_err_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void Util::fillArrWithRandvf(unsigned int arrSize, float * arr, float minValue, float maxValue){
	for (int i = 0; i < arrSize; i++) {
		arr[i] = minValue + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxValue - minValue)));
	}
}

void Util::fillArrWithRandvui(unsigned int arrSize, unsigned int * arr, unsigned int minValue, unsigned int maxValue)
{
	for (int i = 0; i < arrSize;i++) {
		arr[i] = minValue + (rand() / (RAND_MAX / (maxValue - minValue)));
	}
}


