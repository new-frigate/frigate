#ifndef __FRIGATE_CHAR_NAMES_H__
#define __FRIGATE_CHAR_NAMES_H_

#include <map>
#include <string>
#include "frigate_types.h"

//namespace frigate
//{
    class CharNames
    {
        public:
    		CharNames();
    		/**
    		 * Return:
    		 * id if OK
    		 * -1 else
    		 */
            frigate_name_id_type register_name(std::string name);
    		/**
    		 * Return:
    		 * id if OK
    		 * -1 else
    		 */
            frigate_name_id_type search_name(std::string name);
    		/**
    		 * Return:
    		 * name if exist
    		 * NULL else
    		 */
            char* get_name(const frigate_name_id_type name_id);

        private:
            std::map<frigate_name_id_type, std::string> IdDB;
            int id_count;
    };
//}

#endif /* __FRIGATE_CHAR_NAMES_H__ */
