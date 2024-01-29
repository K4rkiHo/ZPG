// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Scale.h"

Scale::Scale(glm::vec3 vector)
{
	this->vector = vector;
}

glm::mat4 Scale::traverse()
{
	return glm::scale(glm::mat4(1.0f), this->vector);
}
