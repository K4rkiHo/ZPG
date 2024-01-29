// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#pragma once
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class CallBacks {
public:
	int b_x = 0;
	int b_y = 0;
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	static bool R_key_pressed_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool W_key_pressed_callback(GLFWwindow* window);
	static bool S_key_pressed_callback(GLFWwindow* window);
	static bool A_key_pressed_callback(GLFWwindow* window);
	static bool D_key_pressed_callback(GLFWwindow* window);
	static bool F_key_pressed_callback(GLFWwindow* window);
	static bool Q_key_pressed_callback(GLFWwindow* window);
	static bool mouse_callkack(GLFWwindow* window);
	static bool mouse_right_callback(GLFWwindow* window);
	static bool mouse_button_callback_test(GLFWwindow* window, int button, int action, int mods);
	static std::pair<double, double> cursor_callback(GLFWwindow* window);
	static std::pair<int, int> get_window_size_callback(GLFWwindow* window);
};