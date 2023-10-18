#ifndef JSON_NODE_HPP
#define JSON_NODE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

#include "Parser.hpp"

class JsonNode
{
private:
	std::map<std::string, std::string> data;

public:
	JsonNode() {}
	JsonNode(std::string path);

	bool init(const char* path);

	bool write(const char* path);

	bool read(const char* path);

	bool load(std::string str);

	std::string toString();

	int length() { return data.size(); }

	bool contains(std::string key);

	bool asSpecialChar(const std::string& str);

	std::map<std::string, std::string> getData(){ return data; }
	
	//operator
	std::string& operator[](const std::string& key);
};
#include "Verif.hpp"

bool JsonNode::init(const char* path)
{
	std::ifstream file(path);

	if (!file)
	{
		std::ofstream createFile(path);
		if (!createFile)
		{
			std::cerr << "An error occurred when creating the file : " << path << std::endl;
			return false;
		}
		createFile.close();
	}
	return true;
}

bool JsonNode::write(const char* path)
{
	init(path);

	std::ofstream file(path);

	if(file.is_open())
	{
		file << toString() << std::endl;

		file.close();
	}else
	{
		std::cerr << "Error to open file : " << path << std::endl;
		return false;
	}

	return true;
}

bool JsonNode::read(const char* path)
{
	std::ifstream file(path);

	if (file.is_open()) {
		std::string line;
		int count = 0;

		while (std::getline(file, line)) {
			count++;
			return load(line);
		}

		if (count == 0) return false;

		file.close();
	} else {
		std::cerr << "Error to open file : " << path << std::endl;
		return false;
	}
	return true;
}
bool JsonNode::load(std::string str)
{
	if (str.size() == 0) return false;

	if (str.at(0) != '{' || str.at(str.size() - 1) != '}')
	{
		std::cerr << "Str is not a json value : " << str << std::endl;
		return false;
	}


	str.erase(str.begin());
	str.erase(str.end() - 1);

	if (str.length() == 0) return false;

	char tv[510][1020];

	int index = 0;
	int index2 = 0;
	int crochNb = 0;
	bool InStr = false;
	char EChar;

	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (c == '"')
		{
			if (EChar == '\\')
			{
				InStr = true;
			}else
			{
				InStr = false;
			}
		}

		if (c == '{' || c == '[')
		{
			if (!InStr)
			{
				crochNb++;	
				}
		}

		if (c == '}' || c == ']')
		{
			if (!InStr)
			{
				crochNb--;
			}
		}
		if(c == ',' && !InStr && crochNb == 0)
		{
			index++;
			index2 = 0;
		}else
		{
			tv[index][index2] = c;
			index2++;
		}
		EChar = c;
	}

	std::vector<std::string> vec(tv, tv + (index + 1));
		
	memset(tv, 0, sizeof(tv));

	for (std::string line : vec)
	{
		std::vector<std::string> l = split(line.c_str(), ':');

		std::string key = l[0];
		l.erase(l.begin());

		std::string value = join(l, ":");

		//sublime data
		value = supFirstElement(value, ' ');
		value = supFirstElement(value, '\t');
		key = supFirstElement(key, ' ');
		key = supFirstElement(key, '\t');


		key = supLastElement(key, ' ');
		key = supLastElement(key, '\t');
		value = supLastElement(value, ' ');
		value = supLastElement(value, '\t');

		key = supFirstElement(key, '\"');
		key = supLastElement(key, '\"');

		if (value.at(value.length() - 1) == ',')
			value = value.substr(0, value.length() - 1);
		if (value.at(0) == '\"')
			value = value.substr(1);
		if (value.at(value.length() - 1) == '\"')
			value = value.substr(0, value.length() - 1);

		value = replace(value, "\\\"", "\"");
		value = replace(value, "\\\'", "\'");
		value = replace(value, "\\\t", "\t");
		value = replace(value, "\\n", "\n");

		data[key] = value;
	}
	return true;
}

std::string JsonNode::toString() {
	auto it = data.begin();

	std::string r = "";

	r += "{";

	for (const auto& pair : data)
	{
		std::string value = pair.second;
		std::string key = pair.first;


		value = replace(value, "\"", "\\\"");
		value = replace(value, "\'", "\\\'");
		value = replace(value, "\t", "\\\t");
		value = replace(value, "\n", "\\n");
				
				
		if (value == "")
			value = "null";

		if (isInt(value) != 0 || isFloat(value) != 0 || isBool(value) != -1 || value == "null")
		{
			r += "\"" + key + "\": " + value;
		}else
		{
			r += "\"" + key + "\": \"" + value + "\"";
		}

		++it;

		if (it != data.end())
		{
			r += ", ";
		}
	}

	r += "}";

	return r;
}

bool JsonNode::contains(std::string key)
{
	if(data.find(key) != data.end())
		return true;
	else
		return false;
}

bool JsonNode::asSpecialChar(const std::string& str)
{
	std::string specialChars = " !@#$%^&*():;,?./\\§&#'{[|`^à@)]°=+}\"";
	size_t found = str.find_first_of(specialChars);

	if(found != std::string::npos)
		return false;
	else
		return true;
}

std::string& JsonNode::operator[](const std::string& key)
{
	if (!asSpecialChar(key))
	{
		std::cerr << "Forbids letter special characters in key : " << key << std::endl;
		exit(0);
	}else return data[key];
}

#endif