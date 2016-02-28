#include "MathUtil.h"


float MathUtil::factoriel(int n)
{
	int value = 1;
	for (int i = 1; i <= n;i++) {
		value *= i;
	}
	return value;
}

float MathUtil::binomialCoeff(float n, float k)
{
	return (factoriel(n)) /  ( factoriel(k) * factoriel(n-k) );
}

float MathUtil::BernsteingPolynome(float m, float i, float u)
{
	return binomialCoeff(m,i)*std::pow(u,i)*std::pow((1-u), m-i);
}

size_t MathUtil::util3dTex_u(size_t x, size_t z, size_t Lx, size_t Dx)
{
	return size_t(x + (Lx*(z - (Dx*floor(z / Dx)) )));
	//return size_t(x + (Lx*(z)));
}

size_t MathUtil::util3dTex_v(size_t x,size_t y, size_t Ly, size_t Dx)
{
	return size_t(y+(Ly*floor(x/Dx)));
}
