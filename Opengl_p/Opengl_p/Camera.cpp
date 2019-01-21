#include "Camera.h"

Camera::Camera() {
	this->viewMatrix = glm::mat4(1.f); //If we don't set the camera, then we can only assume identity matrix
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
	this->viewMatrix = glm::lookAt(eye, center, up);


}

Camera::~Camera() {
}

void Camera::update()
{

}

void Camera::resetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
	this->viewMatrix = glm::lookAt(eye, center, up);
}


void Camera::handleKeys(ValidKeys currentKey) {
	if (currentKey == ValidKeys::W) {
		this->cameraPosition += this->cameraSpeed * this->cameraFront;
	}
	else if (currentKey == ValidKeys::S) {
		this->cameraPosition -= this->cameraSpeed * this->cameraFront;
	}
	else if (currentKey == ValidKeys::A) {
		this->cameraPosition += glm::normalize(glm::cross(this->cameraUp, this->cameraFront))*this->cameraSpeed;
	}
	else if (currentKey == ValidKeys::D) {
		this->cameraPosition -= glm::normalize(glm::cross(this->cameraUp, this->cameraFront))*this->cameraSpeed;
	}

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

glm::mat4 Camera::getViewMatrix() const {
	return this->viewMatrix;
}
