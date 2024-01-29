// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "BezierLine.h"

BezierLine::BezierLine(std::vector<glm::vec3> points, float t, float delta)
{
	this->points = points;
	this->t = t;
	this->delta = delta;
}

glm::mat4 BezierLine::traverse()
{
	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));

	glm::mat4x3 B;
	for (int i = 0; i < 4; i++)
	{
		B[i] = points[i];
	}

	glm::vec4 parameters = glm::vec4(this->t * this->t * this->t, this->t * this->t, this->t, 1.0f);

	glm::vec3 p = parameters * A * glm::transpose(B);


	if (this->t >= 1.0f || this->t <= 0.0f)
	{
		this->delta *= -1;
	}
	this->t += this->delta;

	return glm::translate(glm::mat4(1.0f), p);
}