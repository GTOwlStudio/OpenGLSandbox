#pragma once

#include <Windows.h>
#include <vector>
#include <glm\glm.hpp>
#include <glm\core\type_mat4x4.hpp>
#include <glm\core\type_vec4.hpp>
//#include <iostream>

class Util
{
public:
	static glm::vec2 getPointPositionOnScreen(glm::mat4 const& matrix, glm::vec4 pPos, int screen_width, int screen_height);
	static std::vector<float> getPointerDataArrayf(int arraySize, std::vector<float> data, int argSize, ...);
	static std::vector<float> getXDimensionArrayf(std::vector<float> arr, unsigned int Xn, unsigned int Xd); //Xn : number of dimmension,  Xd the X dimension to extract
	static void error(const char* format, ...); //Display intance red message
	static void dev(const char* format, ...);//Display intance blue message
	static void conceptor(const char* format, ...);//Display intance blue message
	static void green(const char* format, ...); //Display green message
	static void fillArrWithRandvf(unsigned int arrSize, float *arr, float minValue, float maxValue);
	static void fillArrWithRandvui(unsigned int arrSize, unsigned int *arr, unsigned int minValue, unsigned int maxValue);
	//static void 2DTextureTo3DTexCoord();
	//static void 3DTextureTo2DTexCoords(float vx, float vy, float vz, size_t Dx, size_t Dy, size_t Dz, );

private:
	static HANDLE m_console_err_handle;
};

