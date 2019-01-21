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

glm::mat4 Camera::getViewMatrix() const {
	return this->viewMatrix;
}
