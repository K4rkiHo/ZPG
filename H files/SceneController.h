#pragma once
#include <iostream>
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

#include "Model.h"
#include "Translate.h"
#include "Line.h"

class SceneController {
public:
	int gold_count = 0;
	bool q_pressed = false;
	bool l_pressed = false;
	bool right_mouse_pressed = false;
	bool left_mouse_pressed = false;
	bool f_pressed = false;
	bool flashlight_on = false;
	bool e_pressed = false;
	bool m_pressed = false;
	int clickCount = 0;

	std::vector<glm::vec3> click_pos;
	//glm::vec3 clickPositions[2];
	bool Q_keyPressed(GLFWwindow* window);
	bool M_keyPressed(GLFWwindow* window);
	bool L_keyPressed(GLFWwindow* window);
	bool F_keyPressed(GLFWwindow* window);
	bool E_keyPressed(GLFWwindow* window);
	bool Mouse_right_keyPressed(GLFWwindow* window);
	bool Mouse_left_keyPressed(GLFWwindow* window);
	void RemoveGold_E_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector);
	void RemoveObj_Q_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector);
	void FlashLightControls(GLFWwindow* window, Light* l);
	void PlaceObj_Mouse_right_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector, Camera* camera, Model* model, Material* material, Light* light);
	void ChangeLight_L_keyPressed(GLFWwindow* window, Light* light);
	glm::vec3 Right_mouse_click(GLFWwindow* window, Camera* camera);
};