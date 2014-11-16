#ifndef __FRIGATE_FRIGATE_TYPES_H__
#define __FRIGATE_FRIGATE_TYPES_H__

#include <cinttypes>

/* STL does not understand this type
#define frigate_name_id_type int64_t
*/
#define frigate_name_id_type int


enum Vertex_region_types
{
    FRIGATE_DATA_EXCHANGE_REGION,
    FRIGATE_CODE_REGION
};


#endif /* __FRIGATE_FRIGATE_TYPES_H__ */
