#ifndef CONFIG_INTERACT_NDL
#define CONFIG_INTERACT_NDL

#include <iostream>
#include <fstream>

#include "TInteract.hpp"

#if defined(_WIN32) || defined(_WIN64)
	#include <direct.h>
	#define mkdir _mkdir
#else
	#include <sys/stat.h>
#endif

class CInteract
{
	public:
	    TInteract ti;

		CInteract();
		CInteract(TInteract ti);

		std::string ChooseMainDir(bool createPath);
};

CInteract::CInteract() {}

CInteract::CInteract(TInteract ti) {
	ti = ti;
}

std::string CInteract::ChooseMainDir(bool createPath) {
	std::string path = "";

	while(path == "") {
		path = replace(ti.answer("enter a directory for NDLS : "), '\\', '/') + "/";
	}

	path = replace(path, "//", "/");

	if (createPath) {
		std::ifstream folder;
   		folder.open(path);
		if (!folder) {
			int r = mkdir(path.c_str());
			if (r != 0) {
				ti.print("an error occurred when creating the folder! please choose another directory!");
	        	path = ChooseMainDir(true);
			}
		}
	}

	return path;
}


#endif