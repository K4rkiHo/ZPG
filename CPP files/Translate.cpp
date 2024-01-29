// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Translate.h"

Translate::Translate(glm::vec3 vector)
{
	this->vector = vector;
}

glm::mat4 Translate::traverse()
{
	return glm::translate(glm::mat4(1.0f), vector);
}
