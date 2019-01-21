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
		cameraPosition += cameraSpeed * cameraFront;
	}
	else if (currentKey == ValidKeys::S) {
		cameraPosition -= cameraSpeed * cameraFront;
	}
	else if (currentKey == ValidKeys::A) {
		cameraPosition += glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed;
	}
	else if (currentKey == ValidKeys::D) {
		cameraPosition -= glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed;
	}
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
