// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#pragma once
#include "Model.h"
#include "CallBacks.h"
#include "Version.h"
#include "Composite.h"
#include "Rotate.h"
#include "Scale.h"
#include "Translate.h"
#include "Camera.h"
#include "Light.h"
#include "SceneController.h"
#include "Line.h"
#include "BezierLine.h"


#include <ctime> 
#include <cstdlib>

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/random.hpp>	//random number

#include <ft2build.h>
#include FT_FREETYPE_H  

class Scene : public SceneController{
private:
	GLFWwindow* window;
	int height;
	int width;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
public:
	Scene();
	void Scene_Loop();
	void Scene_no1(GLFWwindow* window);
	void Scene_no2(GLFWwindow* window);
	void Scene_no3(GLFWwindow* window);
	void Scene_no4(GLFWwindow* window);
	void Scene_no5(GLFWwindow* window);
	void Scene_no6(GLFWwindow* window);
	void Scene_no7(GLFWwindow* window);
	void Scene_no8(GLFWwindow* window);
};