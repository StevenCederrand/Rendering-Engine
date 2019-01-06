#ifndef FILELOADER_h
#define FILELOADER_h

#include <filesystem>
#include <iostream>
#include <list>
/* Fileloader. This may parse data of certain filetypes. */

class Fileloader {
public:
	Fileloader();
	~Fileloader();


		
	void loadFile(std::string path);

private:
	bool validType(std::string path);



private:

	std::vector<std::string> validFiletypes;


};


#endif