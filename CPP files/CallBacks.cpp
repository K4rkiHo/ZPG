// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "CallBacks.h"

void CallBacks::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void CallBacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void CallBacks::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void CallBacks::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void CallBacks::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void CallBacks::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n");
}

void CallBacks::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}

bool CallBacks::R_key_pressed_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_R) {
			return true;
		}
	}
	else {
		return false;
	}
}

bool CallBacks::W_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
}

bool CallBacks::S_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
}

bool CallBacks::A_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
}

bool CallBacks::D_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
}

bool CallBacks::F_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS);
}

bool CallBacks::Q_key_pressed_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
}

bool CallBacks::mouse_callkack(GLFWwindow* window)
{
	return (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
}

bool CallBacks::mouse_right_callback(GLFWwindow* window)
{
	return (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
}

std::pair<double, double> CallBacks::cursor_callback(GLFWwindow* window)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return std::make_pair(xPos, yPos);
}

std::pair<int, int> CallBacks::get_window_size_callback(GLFWwindow* window)
{
	int height, width;
	glfwGetFramebufferSize(window, &height, &width);
	return std::make_pair(height, width);
}
