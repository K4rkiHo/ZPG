 // ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 vector, float rotate_speed)
{
	this->angle = angle;
	this->vector = vector;
	this->rotate_speed = rotate_speed;
}

glm::mat4 Rotate::traverse()
{
	this->angle += this->rotate_speed;
	return glm::rotate(glm::mat4(1.0f), this->angle, this->vector);
}