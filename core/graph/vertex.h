#ifndef __FRIGATE_VERTEX_H__
#define __FRIGATE_VERTEX_H__

#include "../line_dynamic_array.h"
#include "../frigate_types.h"
#include <fstream>

namespace frigate
{

    class Vertex;

    struct Vertex_region
    {
      enum Vertex_region_types region_type;
      void *region;
    };

    /**
     * This class is need for possibility of multiple exchanges in one vertex
     * It contains IDs of opposite vertices
     */
    class ExchangeBlock
    {
    protected:
    	frigate_name_id_type name_id;
    	Line_dynamic_array<frigate_name_id_type> send;
    	Line_dynamic_array<frigate_name_id_type> recv;

	public:
    	ExchangeBlock(){};
        ~ExchangeBlock(){};
        void toFile(std::ofstream& out);
        ExchangeBlock* copy();
        int addSend(char*);
        int addRecv(char*);
    };

    /**
     * Template class contains code blocks and exchange blocks
     * in arbitrary order. Every vertex must have its template
     */
    class VertexTemplate
    {
    protected:
    	frigate_name_id_type vt_name_id;
    	Line_dynamic_array<Vertex_region> inside_blocks;
	public:
    	VertexTemplate():vt_name_id(-1), inside_blocks(){}
    	virtual ~VertexTemplate(){}
    	VertexTemplate* copy();
    	void deepCopy(Vertex* child);
    	int setName(char*);
        void toFile(std::ofstream& out);
        int setVerticeBlocks(Line_dynamic_array<Vertex_region>&);
    };

    /**
     * Vertex class is specific vertex.
     * Several vertices may have same template
     */
    class Vertex: public VertexTemplate
    {
    protected:
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;

    public:
    	~Vertex(){}
    	Vertex():name_id(-1), template_name_id(-1){}
    	int setTemplateName(char*);
        void toFile(std::ofstream& out);
        Vertex* copy();
    };


} /* End namespace frigate */



#endif /* __FRIGATE_VERTEX_H__ */

