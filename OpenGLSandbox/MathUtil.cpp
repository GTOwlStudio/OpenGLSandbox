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
