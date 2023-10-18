#ifndef CONFIG_NDL
#define CONFIG_NDL

#if defined(_WIN32) || defined(_WIN64)
	#include <direct.h>
	#define mkdir _mkdir
#else
	#include <sys/stat.h>
#endif

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

#include <map>
#include <cstring>

#include "JsonMin/Json.hpp"

#include "Interact/CInteract.hpp"
#include "Interact/TInteract.hpp"

class Config
{
public:
	JsonNode dirNode;
	JsonNode config;

	std::string dir = "";

	Config();
	
	bool init();
	void save();

	void initPreset();
	bool createUser(std::string usr);
};

Config::Config() {

}

bool Config::init() {
	std::string path = "config.json";

	if (!dirNode.read(path.c_str())) {
		dirNode.init(path.c_str());

		if (std::getenv("USERPROFILE") == nullptr){
			dir = CInteract(TInteract()).ChooseMainDir(true);
		}else{
			dir = replace(std::string(std::getenv("USERPROFILE")), '\\', '/') + "/NDLS/";
			int r = mkdir(dir.c_str());

			if (r != 0) {
				dir = CInteract(TInteract()).ChooseMainDir(true);
			}
		}
		dirNode["dir"] = dir;

		initPreset();

		save();

		return false;
	}else{
		dir = replace(dirNode["dir"], '\\', '/') + "/";
		std::string path = dir + "/config.json";

		if (!config.read(path.c_str())) {
			if (config.write(path.c_str())) {
				initPreset();
				return true;
			}
			dirNode = JsonNode();

			dirNode.write("config.json");

			dir = "";

			init();

			return false;
		}

	}

	dir = replace(dir, "//", "/");

	return true;
}

void Config::save() {
	dirNode.write("config.json");
	config.write(std::string(dir + "config.json").c_str());
}

void Config::initPreset() {
	//config file
	std::string cFile = dir + "config.json";
	config.write(cFile.c_str());

	//create main folder
	mkdir(std::string(dir + "tmp/").c_str());
	mkdir(std::string(dir + "cache/").c_str());
	mkdir(std::string(dir + "app/").c_str());
	mkdir(std::string(dir + "usr/").c_str());
	mkdir(std::string(dir + "bin/").c_str());
}

bool Config::createUser(std::string usr) {
	std::string uFolder = dir + "usr/" + usr + "/";
	std::cout << uFolder << std::endl;
	int r = mkdir(uFolder.c_str());

	if (r != 0) return false;

	mkdir(std::string(uFolder + "desktop/").c_str());
	mkdir(std::string(uFolder + "pictures/").c_str());
	mkdir(std::string(uFolder + "movies/").c_str());
	mkdir(std::string(uFolder + "download/").c_str());
	mkdir(std::string(uFolder + "music/").c_str());
	mkdir(std::string(uFolder + "documents/").c_str());

	return true;
}

#endif