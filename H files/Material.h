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

//#include "stb_image.h"

#include "ShaderProgram.h"
#include "Subject.h"

#include <SOIL.h>

class ShaderProgram;

class Material : public Subject {
public:
	GLuint textureID = -9999;
	GLuint temp = 1;
	float repeat = 1;
	std::vector<const char*> texture_path_vec;
	const char* texturePath;
	glm::vec4 materialColor;
	glm::vec3 materialColor1;
	Material(glm::vec4 materialColor);
	Material(glm::vec3 materialColor1);
	Material(std::vector<const char*> texture_path_vec);
	Material(const char* texturePath);
	void CreateTexture();
	void CreateSkyboxTexture();
	GLuint getTexture();
	void setColor();
	void setTexture();
	void setTextureSkybox();
	void setTextureRepeat(float repeat);
};