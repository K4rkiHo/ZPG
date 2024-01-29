// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Composite.h"

void Composite::Add(Transform* transformation)
{
	this->children.push_back(transformation);
}

glm::mat4 Composite::traverse()
{
	glm::mat4 matice = glm::mat4(1.0f);
	for (int i = 0; i < this->children.size(); i++)
	{
		matice = this->children[i]->traverse() * matice;
	}
	return matice;
}