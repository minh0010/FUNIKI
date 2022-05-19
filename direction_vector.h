#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

struct Direction_Vector
{
	Direction_Vector()
	{
		a = 0.0;
		b = 0.0;
	}

	Direction_Vector(const float& a_, const float& b_)
	{
		a = a_;
		b = b_;
	}

	Direction_Vector& operator-(Direction_Vector num)
	{
		this->a = this->a - num.a;
		this->b = this->b - num.b;
		return *this;
	}

	Direction_Vector& operator+(Direction_Vector num)
	{
		this->a = this->a + num.a;
		this->b = this->b + num.b;
		return *this;
	}

	Direction_Vector& operator/(float num)
	{
		this->a = (float)(this->a / num);
		this->b = (float)(this->b / num);
		return *this;
	}

	float Get_Vector_Length()
	{
		return (float)(sqrt(pow(a, 2) + pow(b, 2)));
	}

	void print()
	{
		std::cout << a << " " << b << std::endl;
	}

	float a;
	float b;
};

float Cosin_Value_Between_Two_Vector(Direction_Vector v1, Direction_Vector v2);