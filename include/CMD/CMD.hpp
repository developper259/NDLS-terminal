#ifndef CMD_NDL
#define CMD_NDL

#include <iostream>
#include <stdlib.h>

#include "Interact/TInteract.hpp"
#include "User/LocalUser.hpp"
#include "JsonMin/Parser.hpp"

#include "Config.hpp"
#include "CmdParsed.hpp"

class CMD
{
public:

	TInteract ti;
	Config config;
	LocalUser lu;

	CMD();
	CMD(TInteract ti, Config config, LocalUser lu);

	void run();
	CmdParsed parse(std::string value);
	void execute(CmdParsed cmd);
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

		if (v != "") {
			CmdParsed c = parse(v);
			execute(c);
		}
	}
}

CmdParsed CMD::parse(std::string value) {
	CmdParsed cmdP = CmdParsed();
	char tv[510][1020];

	int index = 0;
	int index2 = 0;
	bool isStr = false;

	char oldChar;

	for (size_t i = 0; i < value.size(); ++i)
	{
		char c = value.at(i);

		if (c == '\"' && oldChar != '\\') isStr = !isStr;
		if (c == ' ' && oldChar != ' ' && !isStr) {
			index++;
			index2 = 0;
		}

		if (c != ' ' || isStr){
			tv[index][index2] = c;
			index2++;
		}
		oldChar = c;
	}

	for (int i = 0; i <= index; ++i)
	{
		std::string str(tv[i]);
		if (i == 0) {
			cmdP.cmd = str;
		}else if (str.at(0) == '\"') {
			str = supFirstElement(str, '\"');
			str = supLastElement(str, '\"');
			cmdP.args.push_back(str);
		}else{
			cmdP.args.push_back(str);
		}
	}

	memset(tv, 0, sizeof(tv));

	return cmdP;
}

void CMD::execute(CmdParsed cmd) {

}

#endif