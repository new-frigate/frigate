#ifndef __FRIGATE_CHAR_NAMES_H__
#define __FRIGATE_CHAR_NAMES_H_

#include <map>
#include <string>
#include "frigate_types.h"
#include "line_dynamic_array.h"

namespace frigate
{
    class CharNames
    {
        public:
    		CharNames();
            frigate_name_id_type register_name(std::string name);
            frigate_name_id_type search_name(std::string name);
            char* get_name(const frigate_name_id_type name_id);

        private:
            std::map<frigate_name_id_type, std::string> IdDB;
            int id_count;
    };
}

#endif /* __FRIGATE_CHAR_NAMES_H__ */
