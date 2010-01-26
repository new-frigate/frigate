#ifndef __FRIGATE_CHAR_NAMES_H__
#define __FRIGATE_CHAR_NAMES_H_

#include "frigate_types.h"


namespace frigate
{
    class Char_names
    {
        public:
            frigate_name_id_type register_name(const char *name);
            frigate_name_id_type search_name(const char *name);
            char* read_name_unsafe(const frigate_name_id_type name_id);
    };
}

#endif /* __FRIGATE_CHAR_NAMES_H__ */
