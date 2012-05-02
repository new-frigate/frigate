#include "char_names.h"

namespace frigate
{

	CharNames::CharNames()
	{
		id_count = 0;
	}

	frigate_name_id_type CharNames::register_name(std:: string name)
	{
		IdDB.insert( std::pair<int, std::string >(id_count, name));
		id_count++;
		return (frigate_name_id_type)id_count;
	}

	frigate_name_id_type CharNames::search_name(std::string name)
	{
		std::map<frigate_name_id_type, std::string>::iterator it;
		for(it = IdDB.begin(); it != IdDB.end(); it++)
		{
			if((*it).second == name)
			{
				return (*it).first;
			}
		}
		return -1;
	}

	char* CharNames::get_name(const frigate_name_id_type name_id)
	{
		std::map<frigate_name_id_type, std::string>::iterator it;
		it = IdDB.find(name_id);
		if(it != IdDB.end())
		{
			return (char*)(*it).second.c_str();
		}
		return NULL;
	}

}
