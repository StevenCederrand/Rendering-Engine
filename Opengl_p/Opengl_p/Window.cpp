
/*
	|-------------------------------- A BIT OF SETUP --------------------------------|
	This project uses a similare setup of window management as learnopengl.com. 
	For this to work we need to make sure that the following steps are followed. 
	Otherwise errors will occur. 

	>>Make sure that the solution is set to Debug & x86
	>>Properties->WindowsSDKVersion->latest
	>>Properties->VC++ Directories->Include Directories
	>>Properties->VC++ Directories->Library Directories
	>>Properties->C/C++->Preprocessor->Preprocessor Definitions->"_CRT_SECURE_NO_WARNINGS; GLFW_INCLUDE_NONE;"
	>>Properties->Linker->Input->Additional Dependencies->"opengl32.lib;glfw3.lib;"

*/
#include "Application.h" //Application. This is my head 
#include <fstream>
#include <iostream>

int main() {
	
	Application* app = new Application(1280, 900);

	app->update();

	return 0;
}