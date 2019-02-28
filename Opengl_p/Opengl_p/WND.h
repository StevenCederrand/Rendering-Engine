#ifndef WND_h
#define WND_h

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Containers.h"
#include <iostream>
#include <utility>

class WND {
public:
	WND();
	WND(int width, int height);
	~WND();

	//Start generates three different leaks in memory
	int start();

	void update();
	void inputKey(ValidKeys& key);
	void close();
	std::pair<int, int> getResolution() const;

	GLFWwindow* getWindow() const;
private:
	//Window Width & height
	int WNDW = 0;
	int WNDH = 0;
	GLFWwindow* window;
	GLint flags;
};

#endif
