#include "direction_vector.h"

float Cosin_Value_Between_Two_Vector(Direction_Vector v1, Direction_Vector v2)
{
	return (float)((v1.a * v2.a + v1.b * v2.b) / (sqrt(pow(v1.a, 2) + pow(v1.b, 2)) * sqrt(pow(v2.a, 2) + pow(v2.b, 2))));
}