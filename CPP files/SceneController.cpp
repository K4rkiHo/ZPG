#include "SceneController.h"
#include <vector>

bool SceneController::Q_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetKey(window, GLFW_KEY_Q);

	if (keyState == GLFW_PRESS && !this->q_pressed)
	{
		this->q_pressed = true;
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->q_pressed = false;
	}

	return false;
}

bool SceneController::M_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetKey(window, GLFW_KEY_M);

	if (keyState == GLFW_PRESS && !this->m_pressed)
	{
		this->m_pressed = true;
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->m_pressed = false;
	}

	return false;
}

bool SceneController::L_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetKey(window, GLFW_KEY_L);

	if (keyState == GLFW_PRESS && !this->l_pressed)
	{
		this->l_pressed = true;
		this->clickCount++;
		if (this->clickCount > 4)
		{
			this->clickCount = 1;
		}
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->l_pressed = false;
	}

	return false;
}

bool SceneController::F_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetKey(window, GLFW_KEY_F);

	if (keyState == GLFW_PRESS && !this->f_pressed)
	{
		this->f_pressed = true;

		// Pøepnout stav baterky
		this->flashlight_on = !this->flashlight_on;

		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->f_pressed = false;
	}

	return false;
}

bool SceneController::E_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetKey(window, GLFW_KEY_E);

	if (keyState == GLFW_PRESS && !this->e_pressed)
	{
		this->e_pressed = true;
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->e_pressed = false;
	}

	return false;
}

bool SceneController::Mouse_right_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

	if (keyState == GLFW_PRESS && !this->right_mouse_pressed)
	{
		this->right_mouse_pressed = true;
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->right_mouse_pressed = false;
	}

	return false;
}

bool SceneController::Mouse_left_keyPressed(GLFWwindow* window)
{
	int keyState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (keyState == GLFW_PRESS && !this->left_mouse_pressed)
	{
		this->left_mouse_pressed = true;
		return true;
	}
	else if (keyState == GLFW_RELEASE)
	{
		this->left_mouse_pressed = false;
	}

	return false;
}

void SceneController::RemoveGold_E_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector)
{
	if (SceneController::E_keyPressed(window) == true)
	{
		glfwSwapBuffers(window);
		std::cout << "E pressed" << std::endl;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLuint index;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = height - y;
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("[STENCIL] Selected with id %d\n", index);

		if (index >= 0 && index < model_vector.size())
		{
			if (model_vector[index]->getObj_path() == "./Models/3D_Models/gold.obj")
			{
				model_vector.erase(model_vector.begin() + index);

				this->gold_count++;
				std::cout << "---------------------" << std::endl;
				std::cout << "| NUMBER OF GOLD: " << this->gold_count << " |" << std::endl;
				std::cout << "---------------------" << std::endl;
			}
		}

		glfwSwapBuffers(window);
	}
}

void SceneController::RemoveObj_Q_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector)
{
	if (SceneController::Q_keyPressed(window))
	{
		glfwSwapBuffers(window);
		std::cout << "Q pressed" << std::endl;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLuint index;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = height - y;
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("[STENCIL] Selected with id %d\n", index);
		model_vector.erase(model_vector.begin() + index);
		glfwSwapBuffers(window);
	}
}

void SceneController::FlashLightControls(GLFWwindow* window, Light* l)
{
	if (SceneController::F_keyPressed(window) == true)
	{
		if (this->flashlight_on)
		{
			l->setLightON();
			l->refrestLight();
		}
		else
		{
			l->setLightOFF();
			l->refrestLight();
		}
	}
}

void SceneController::PlaceObj_Mouse_right_keyPressed(GLFWwindow* window, std::vector<Model*>& model_vector, Camera* camera, Model* model, Material* material, Light* light)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	y = height - y;

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

	glm::vec3 screenX = glm::vec3(x, y, depth);
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = camera->getProjectionMatrix();
	glm::vec4 viewPort = glm::vec4(0, 0, width, height);
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	printf("Index: %d", index);

	model->addTransform(new Translate(pos));

	camera->attach(model->getShaderProgram());
	material->attach(model->getShaderProgram());
	light->attach(model->getShaderProgram());
	light->refrestLight();
	material->setTexture();

	model_vector.push_back(model);
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void SceneController::ChangeLight_L_keyPressed(GLFWwindow* window, Light* light)
{
	if (SceneController::L_keyPressed(window))
	{
		light->setTypeLight(this->clickCount);
		light->refrestLight();
	}
	if (SceneController::F_keyPressed(window) == true)
	{
		if (this->flashlight_on)
		{
			light->setLightON();
			light->refrestLight();
		}
		else
		{
			light->setLightOFF();
			light->refrestLight();
		}
	}
}

glm::vec3 SceneController::Right_mouse_click(GLFWwindow* window, Camera* camera)
{
	//if (SceneController::Mouse_left_keyPressed(window))
	//{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = height - y;

		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		glm::vec3 screenX = glm::vec3(x, y, depth);
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		return pos;
	/*}*/
}


