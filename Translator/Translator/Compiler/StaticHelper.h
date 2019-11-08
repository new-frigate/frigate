#ifndef STATICHELPER_H
#define STATICHELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>


class StaticHelper {
public:
	
	static std::string location_prefix;
	
	static std::set<std::string> vertex_templates;
	
	static std::string readFile(std::string filename);
	
	static std::string autoNamePref;
	static int autoNameID;
	
	static void genNamePref();
	static std::string autoName();
	static void badPref();
};

#endif /* STATICHELPER_H */

