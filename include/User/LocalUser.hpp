#ifndef LOCAL_USER_NDL
#define LOCAL_USER_NDL

#include "Interact/TInteract.hpp"

#include "User.hpp"
#include "UserStats.hpp"

#include "JsonMin/Json.hpp"
#include "Crypt.hpp"

class LocalUser
{
	public:
		std::string username;
		std::string password;

		User u;


		LocalUser();
		LocalUser(std::string username, std::string password, User u);
		LocalUser(std::string username, std::string password);
		LocalUser(std::string password, User u);

		bool save(std::string path);
		bool load(std::string path);
};

LocalUser::LocalUser() {}

LocalUser::LocalUser(std::string username, std::string password, User u) {
	this->username = username;
	this->password = password;
	this->u = u;
}

LocalUser::LocalUser(std::string username, std::string password) {
	this->username = username;
	this->password = password;
}

LocalUser::LocalUser(std::string password, User u) {
	this->username = u.US.username;
	this->password = password;
	this->u = u;
}

bool LocalUser::save(std::string path) {
	JsonNode n;
	Crypt c = Crypt("key.ndl");

	n["username"] = username;
	n["password"] =password;

	/*if (!u.isEmpty()) {
		n["Nid"] = u.id;
	}*/

	std::string dst = path + "user.ndl";

	std::ofstream file(dst.c_str());

	if(file.is_open())
	{
		file << c.encode(n.toString()) << std::endl;

		file.close();
	}else
	{
		TInteract().printError("Error to open file : " + dst);
		return false;
	}

	return true;
}

bool LocalUser::load(std::string path) {
	JsonNode n;
	Crypt c = Crypt("key.ndl");
	std::string dst = path + "user.ndl";

	std::ifstream file(dst.c_str());

	if (file.is_open()) {
		std::string line;
		std::getline(file, line);

		bool r = n.load(c.decode(line));

		if (!r || n.length() < 2) return false;

		username = n["username"];
		password = n["password"];

		if (username == "" || password == "") return false;
		
		file.close();

		return true;
	}else
	{
		TInteract().printError("Error to open file : " + dst);
		return false;
	}

	return false;
}

#endif