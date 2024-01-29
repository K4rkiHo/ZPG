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

#include "Camera.h"
#include "Observer.h"
#include "ShaderLoader.h"
#include "Light.h"
#include "Material.h"

class Camera;
class Light;
class Material;
class ShaderProgram : public Observer, public ShaderLoader {
private:
	std::string shader_name;
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader, std::string shader_name);
	void UseShaderProgram();
	GLuint setSpecs(const std::string& uniformName, glm::mat4 matice);
	GLuint setSpecs(const std::string& uniformName, glm::vec4 lightVec);
	GLuint setSpecs(const std::string& uniformName, glm::vec3 lightVec);
	GLuint setSpecs(const std::string& uniformName, float stats);
	GLuint setSpecs(const std::string& uniformName, GLuint idTexture);
	void notify(void* camera, std::string choose);
	void unUseShaderProgram();
};