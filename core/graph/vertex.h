#ifndef __FRIGATE_VERTEX_H__
#define __FRIGATE_VERTEX_H__

#include "line_dynamic_array.h"
#include "frigate_types.h"

namespace frigate
{

   
    struct Vertex_region
    {
      enum Vertex_region_types region_type;
      void *region;  
    };




    
} /* End namespace frigate */



#endif /* __FRIGATE_VERTEX_H__ */

