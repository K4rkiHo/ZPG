// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************
// Credits: https://learnopengl.com/Getting-started/Camera

#pragma once
#include "Camera.h"
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Subject.h"
#include "CallBacks.h"
#include "ShaderProgram.h"

class ShaderProgram;

class Camera : public Subject
{
private:
    glm::vec3 up;
    float camspeed = 0.001f;
    float mouseSensitivity = 0.1f;
    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float lastX;
    float lastY;
    bool mousePressed;
public:
    bool f_pressed;
    glm::vec3 eye;
    glm::vec3 target;
    Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    void move(GLFWwindow* window, double delta);
    void mouseMove(double xPosIn, double yPosIn, bool MousePressed);
    void LightControl(GLFWwindow* window);
    void updateDirection(glm::vec3 direction);
    void updateViewMatrix();
    void updateProjectionMatrix();
    void resizeWindow(GLFWwindow* window);
    void updateProjectionMatrixWithParameters(int height, int wight);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};