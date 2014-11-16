#ifndef __FRIGATE_CODE_BLOCK_H__
#define __FRIGATE_CODE_BLOCK_H__

/*TODO
 *
 * Change it to stdio.h simulteneously with
 * functions which uses ofstream
 */
#include <fstream>

namespace frigate
{


    /**
     * This class contains links to blocks of code in C/C++ for vertices or "header", 
     * "root" and "tail" in graph.
     * Also it contains info about i/o and calculation costs.
     */
    class CodeBlock
    {
    protected:
        /**
         * The string contans a code for vertices in subgraphs or globals like 
         * "header", "root", "tail".
         *
         * If value is NULL you should read next field called 'file_name'.
         */
        char* code;
        /**
         * The string with name of file where code is written. 
         * The NULL value shows that 'code' field are used. If values of 'code'  and 'file_name' are NULL 
         * then this code block is unusable.
         */
        char* file_name;

        char* io_volume;
        char* code_volume;

    public:
        CodeBlock(const CodeBlock&);
        CodeBlock():code(NULL), file_name(NULL), io_volume(NULL), code_volume(NULL){};
        CodeBlock& operator=(const CodeBlock&);
        int setCode(char* _code);
        int setIOVolume(char*);
        int setCodeVolume(char*);
        int setFileName(char* file_name);
        void toFile(std::ofstream& out);
        bool isEmpty() const
        {
            if(!code && !file_name) return true;
            return false;
        }
        CodeBlock* copy();
        ~CodeBlock();
    };

} /* End namespace frigate */

#endif /* __FRIGATE_CODE_BLOCK_H__ */


