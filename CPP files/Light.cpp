// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Light.h"

Light::Light(glm::vec3 lightPos, glm::vec4 lightColor, glm::vec3 lightDirection, float ambientStrength, float specularStrength, float shininess, float typeLight, float light_on)
{
	this->lightPos = lightPos;
	this->lightColor = lightColor;
	this->lightDirection = lightDirection;
	this->ambientStrength = ambientStrength;
	this->specularStrength = specularStrength;
	this->shininess = shininess;
	this->typeLight = typeLight;
	this->light_on = light_on;
}

void Light::refrestLight()
{
	notifyObservers(this, "light");
}

void Light::setLightON()
{
	this->light_on = 1.0f;
}

void Light::setLightOFF()
{
	this->light_on = 0.0f;
}

void Light::setTypeLight(int number)
{
	this->typeLight = number;
}
