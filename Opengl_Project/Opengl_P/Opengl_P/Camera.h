#ifndef CAMERA_h
#define CAMERA_h

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera {
public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	~Camera();


	void resetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	glm::mat4 getViewMatrix() const;
private:
	glm::mat4 viewMatrix;

};


#endif