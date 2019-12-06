#ifndef STATICHELPER_H
#define STATICHELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>


class StaticHelper {
public:
	
	static std::string location_prefix;
	
	static std::set<std::string> vertex_templates;
	
	static std::string readFile(std::string filename);
	
	static std::string autoNamePref;
	static int autoNameID;
	
	static std::map<std::string, std::vector<std::string> > parameters;
	
	static void genNamePref();
	static std::string autoName();
	static void badPref();
	static bool registerParam(std::string name, std::vector<std::string> val);
	
	static std::string replaceAll(std::string &in, std::string &sub, std::string &rep);
};

#endif /* STATICHELPER_H */

