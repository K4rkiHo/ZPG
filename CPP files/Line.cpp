// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Line.h"

Line::Line(float t, float delta, glm::vec3 A, glm::vec3 B)
{
	this->t = t;
	this->delta = delta;
	this->A = A;
	this->B = B;
}

glm::mat4 Line::traverse()
{
	glm::vec3 point = this->A + (this->B - this->A) * this->t;
	if (t > 1.0f || t < 0.0f) {
		delta *= -1.0f;
	}
	t += delta;

	return glm::translate(glm::mat4(1.0f), point);
}
