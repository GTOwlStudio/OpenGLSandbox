#pragma once

#include <cmath>

class MathUtil
{
public:
	static float factoriel(int value);
	static float binomialCoeff(float m, float i);
	static float BernsteingPolynome(float m, float i, float value);
	static int sign(int x);
	static size_t util3dTex_u(size_t x, size_t z, size_t Lx, size_t Dx);
	static size_t util3dTex_v(size_t x, size_t y, size_t Ly, size_t Dx);

};

