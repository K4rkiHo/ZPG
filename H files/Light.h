// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
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

#include "ShaderProgram.h"
#include "Subject.h"

class ShaderProgram;

class Light : public Subject {
public:
	glm::vec3 lightPos;
	glm::vec4 lightColor;
	glm::vec3 lightDirection;
	float ambientStrength;
	float specularStrength;
	float shininess;
	float typeLight;
	float light_on;
	Light(glm::vec3 lightPos,glm::vec4 lightColor, glm::vec3 lightDirection,float ambientStrength,float specularStrength,float shininess, float typeLight);
	Light(glm::vec3 lightPos, glm::vec4 lightColor, glm::vec3 lightDirection, float ambientStrength, float specularStrength, float shininess, float typeLight, float light_on);
	void refrestLight();
	void setLightON();
	void setLightOFF();
	void setTypeLight(int number);
};