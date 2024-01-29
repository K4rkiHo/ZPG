// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#pragma once
#include <vector>
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <iostream>

#include "Transform.h"

class BezierLine : public Transform {
	std::vector<glm::vec3> points;
	float t;
	float delta;
public:
	BezierLine(std::vector<glm::vec3> points, float t, float delta);
	glm::mat4 traverse();
};