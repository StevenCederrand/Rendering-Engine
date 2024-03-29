#include "Camera.h"

Camera::Camera() {
	this->viewMatrix = glm::mat4(1.f); //If we don't set the camera, then we can only assume identity matrix
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, GLFWwindow* window) {
	this->viewMatrix = glm::lookAt(eye, center, up);
	this->window = window;
	//this should make the mouse invisible and able to move how far we want
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->cursorHidden = true;

	this->shadowViewMatrix = glm::lookAt(this->shadowCameraPosition, this->shadowCameraUp, this->shadowCameraFront);		
}

Camera::~Camera() {
}

void Camera::update()
{
	mouse_callback(this->window);

}

void Camera::resetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
	this->viewMatrix = glm::lookAt(eye, center, up);
}


void Camera::handleKeys(ValidKeys currentKey, float yPos, float deltaTime) {
	if (currentKey == ValidKeys::E) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->cursorHidden = false;
		return;
	}
	if (currentKey == ValidKeys::H) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		this->cursorHidden = true;
		return;
	}

	float velocity = this->cameraSpeed * deltaTime;

	if (currentKey == ValidKeys::W) {
		this->cameraPosition += velocity * this->cameraFront;
	}
	else if (currentKey == ValidKeys::S) {
		this->cameraPosition -= velocity * this->cameraFront;
	}
	else if (currentKey == ValidKeys::A) {
		this->cameraPosition += glm::normalize(glm::cross(this->cameraUp, this->cameraFront))*velocity;
	}
	else if (currentKey == ValidKeys::D) {
		this->cameraPosition -= glm::normalize(glm::cross(this->cameraUp, this->cameraFront))*velocity;
	}
	else if (currentKey == ValidKeys::Q) {
		if(this->cameraSpeed==1.f)
		{
			this->cameraSpeed = 10.5f;
		}
		else if (this->cameraSpeed == 10.5f)
		{
			this->cameraSpeed = 1.f;
		}
	}
	if (currentKey == ValidKeys::I || currentKey == ValidKeys::K || currentKey == ValidKeys::J || currentKey == ValidKeys::L) {

		if (currentKey == ValidKeys::I) {
			this->shadowCameraPosition += glm::vec3(1, 0, 0); //velocity * this->shadowCameraFront;
		}
		else if (currentKey == ValidKeys::K) {
			this->shadowCameraPosition -= glm::vec3(1, 0, 0); //velocity * this->shadowCameraFront;
		}
		else if (currentKey == ValidKeys::J) {
			this->shadowCameraPosition -= glm::vec3(0, 0, 1); //glm::normalize(glm::cross(this->shadowCameraUp, this->shadowCameraFront))*velocity;
		}
		else if (currentKey == ValidKeys::L) {
			this->shadowCameraPosition += glm::vec3(0, 0, 1); //glm::normalize(glm::cross(this->shadowCameraUp, this->shadowCameraFront))*velocity;
		}
		this->shadowViewMatrix = glm::lookAt(this->shadowCameraPosition, this->shadowCameraUp, this->shadowCameraFront);
	}

	glm::vec3 temp = this->cameraPosition;
	temp.y= yPos;
	//cameraPosition.y = yPos+1;
	this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	
}

glm::vec3 Camera::getCameraPosition() const
{
	return this->cameraPosition;
}

glm::vec3 Camera::getCameraUp() const
{
	return this->cameraUp;
}

glm::vec3 Camera::getCameraFront() const
{
	return this->cameraFront;
}

void Camera::mouse_callback(GLFWwindow * window)// ,double xpos, double ypos)
{
	float mouse_x = 640.0f;
	float mouse_y = 450.0f;

	glfwGetCursorPos(window, &xpos, &ypos);

	if (this->cursorHidden) {
		glfwSetCursorPos(window, mouse_x, mouse_y);

		if (firstTime == true) {
			firstTime = false;
			xpos = mouse_x;
			ypos = mouse_y;
		}

		float x_offset = (float)xpos - mouse_x;
		float y_offset = mouse_y - (float)ypos;

		float mouse_sensetivity = 0.1f;
		x_offset *= mouse_sensetivity;
		y_offset *= mouse_sensetivity;

		yaw += x_offset;
		pitch += y_offset;

		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		glm::vec3 front2;
		front2.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front2.y = sin(glm::radians(pitch));
		front2.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		this->cameraFront = glm::normalize(front2);
		this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	}

}

glm::mat4 Camera::getViewMatrix() const {
	return this->viewMatrix;
}

glm::mat4 Camera::getshadowViewMatrix() const {
	return this->shadowViewMatrix;
}

glm::vec3 Camera::getshadowPosition() const
{
	return this->shadowCameraPosition;
}

std::pair<double, double> Camera::getMousePosition() const {
	if (cursorHidden) {
		return std::make_pair(-1, -1);
	}
	return std::make_pair(xpos, ypos);
}