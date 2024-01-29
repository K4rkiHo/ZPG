// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKO�KA - (KAR0229)
//
// ***********************************************************************

#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Transform.h"

class Rotate : public Transform	
{
	float angle;
	glm::vec3 vector;
	float rotate_speed;
public:
	Rotate(float angle, glm::vec3 vector, float rotate_speed);
	glm::mat4 traverse();
};