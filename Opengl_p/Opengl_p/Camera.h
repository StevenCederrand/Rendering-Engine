#ifndef CAMERA_h
#define CAMERA_h

#include "Containers.h"
#include "WND.h"
#define GLM_ENABLE_EXPERIMENTAL


class Camera {
public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, GLFWwindow* window);
	~Camera();

	void update();
	void resetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	glm::mat4 getViewMatrix() const;
	
	//Handle key presses
	void handleKeys(ValidKeys currentKey, float yPos, float deltaTime);
	
	glm::vec3 getCameraPosition() const;
	glm::vec3 getCameraUp() const;
	glm::vec3 getCameraFront() const;
private:
	glm::mat4 viewMatrix;
	//Variables from Applcation.h
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	float cameraSpeed = 1.f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool firstTime = true;

	void mouse_callback(GLFWwindow* window);//, double xpos, double ypos);
	//save the window so that we can use it in the class
	GLFWwindow* window;
};


#endif