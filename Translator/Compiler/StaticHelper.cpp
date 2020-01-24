#ifndef STATICHELPER
#define STATICHELPER

#include "StaticHelper.h"
#include "../Exceptions/Excepion.h"

//std::set<std::string> StaticHelper::vertex_templates;

std::map<std::string, std::vector<std::string> > StaticHelper::parameters;

//std::string StaticHelper::autoNamePref = "auto_n";
//int StaticHelper::autoNameID = 0;

std::string StaticHelper::location_prefix = "";

std::string StaticHelper::readFile(std::string filename) {
	filename = StaticHelper::location_prefix + filename;
	std::ifstream ifs(filename);
        if (ifs.fail())
            throw Exception("FILE NOT FOUND: ", filename);
	std::string ret( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();
	return ret;
}
/*
void StaticHelper::genNamePref() {
	StaticHelper::autoNameID++;
}

std::string StaticHelper::autoName() {
	return StaticHelper::autoNamePref + "-" + std::to_string(StaticHelper::autoNameID);
}

void StaticHelper::badPref() {
	StaticHelper::autoNamePref += (char)(std::rand() % 26 + 'a');
}
*/
bool StaticHelper::registerParam(std::string name, std::vector<std::string> val) {
	if (StaticHelper::parameters.find(name) != StaticHelper::parameters.end()) {
		return false;
	}
	StaticHelper::parameters.insert(std::pair<std::string, std::vector<std::string> >(name, val));
	return true;
}

std::string StaticHelper::replaceAll(std::string &in, std::string &sub, std::string &rep) {
	while (in.find(sub) != in.npos) {
		in.replace(in.find(sub), sub.length(), rep);
	}
	return in;
}



#endif