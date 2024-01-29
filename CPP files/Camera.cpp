// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************
// Credits: https://learnopengl.com/Getting-started/Camera

#include "Camera.h"
#include "ShaderProgram.h"

//eye = camera position
//target = where camera looking
//up = up vector, where cam is rotate in 3D world

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
    this->eye = eye;
    this->target = target;
    this->up = up;
    this->viewMatrix = glm::lookAt(eye, target, up);
    this->projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::move(GLFWwindow* window, double delta)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * delta;

    if (CallBacks::W_key_pressed_callback(window))
    {
        //printf("W");
        this->eye += cameraSpeed * this->target;
        updateViewMatrix();
    }
    if (CallBacks::S_key_pressed_callback(window))
    {
        //printf("S");
        this->eye -= cameraSpeed * this->target;
        updateViewMatrix();
    }
    if (CallBacks::A_key_pressed_callback(window))
    {
        //printf("A");
        this->eye -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
        updateViewMatrix();
    }
    if (CallBacks::D_key_pressed_callback(window))
    {
        //printf("D");
        this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
        updateViewMatrix();
    }
    notifyObservers(this, "camera");
}

void Camera::mouseMove(double xPosIn, double yPosIn, bool MousePressed)
{
    //conversion from double to float
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    //Check if is mouse pressed
    if (MousePressed == false)
    {
        this->mousePressed = true;
    }

    //if mousedPressed == true, last position X,Y set to xPos and yPos
    if (this->mousePressed == true)
    {
        this->lastX = xPos;
        this->lastY = yPos;
        this->mousePressed = false;
    }

    //Calculate last position of mouse 
    float xOffset = xPos - this->lastX;
    float yOffset = this->lastY - yPos;

    this->lastX = xPos;
    this->lastY = yPos;

    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;

    // add offsets to Yaw and Pitch angle
    this->Yaw += xOffset;
    this->Pitch += yOffset;

    //check if Pitch angle ist more than 89.0f degree
    if (this->Pitch > 89.0f)
    {
        this->Pitch = 89.0f;
    }
    if (this->Pitch < -89.0f)
    {
        this->Pitch = -89.0f;
    }

    //calculate new camera direction with Cos and Sin
    glm::vec3 new_cam_direction;
    new_cam_direction.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    new_cam_direction.y = sin(glm::radians(this->Pitch));
    new_cam_direction.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

    //update Camera direction and view Matrix
    this->updateDirection(glm::normalize(new_cam_direction));
    this->updateViewMatrix();

    //notify all observes whitch are attached to camera and notify all
    notifyObservers(this, "camera");
}

void Camera::LightControl(GLFWwindow* window)
{
    if (CallBacks::F_key_pressed_callback(window))
    {
        this->f_pressed = true;
    }
    else
    {
        this->f_pressed = false;
    }
}

void Camera::updateDirection(glm::vec3 direction)
{
    this->target = direction;
}

void Camera::updateViewMatrix()
{
    this->viewMatrix = glm::lookAt(this->eye, this->eye + this->target, this->up);
}

void Camera::updateProjectionMatrix()
{
    this->projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::resizeWindow(GLFWwindow* window)
{
    std::pair<int, int> size = CallBacks::get_window_size_callback(window);
    updateProjectionMatrixWithParameters(size.first, size.second);
    notifyObservers(this, "camera");
}

void Camera::updateProjectionMatrixWithParameters(int height, int wight)
{
    this->projectionMatrix = glm::perspective(glm::radians(45.0f), (float)height / (float)wight, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}
