#ifndef CMD_NDL
#define CMD_NDL

#include <iostream>
#include <stdlib.h>

#include "Interact/TInteract.hpp"
#include "Config.hpp"
#include "User/LocalUser.hpp"

class CMD
{
public:

	TInteract ti;
	Config config;
	LocalUser lu;

	CMD();
	CMD(TInteract ti, Config config, LocalUser lu);

	void run();
	cmdParsed parse(std::string value);
	void run(cmdParsed cmd);
};

CMD::CMD() {}

CMD::CMD(TInteract ti, Config config, LocalUser lu) {
	this->ti = ti;
	this->config = config;
	this->lu = lu;
}

void CMD::run() {
	std::string username = lu.username;

	while(true) {
		std::string v = ti.answer(username + " $ ");

		if (v != "" || v != nullptr) {
			cmdParsed c = parse(v);
			run(c);
		}
	}
}

#endif