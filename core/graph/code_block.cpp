//Main graph classes functions
#ifndef __FRIGATE_GRAPH_CPP__
#define __FRIGATE_GRAPH_CPP__

#include <string.h>
#include "code_block.h"

namespace frigate{


int CodeBlock::setCode(char* _code)
{
	if(code == NULL && file_name == NULL)
	{
		code = new char[strlen(_code)+1];
		strcpy(code, _code);
		return 0;
	}
	return 1;
}

int CodeBlock::setFileName(char* filename)
{
	if(code == NULL && file_name == NULL)
	{
		file_name = new char[strlen(filename)+1];
		strcpy(file_name, filename);
		return 0;
	}
	return 1;
}

int CodeBlock::setIOVolume(char* vol)
{
	io_volume = new char[strlen(vol)+1];
	if(io_volume == NULL)
		return -1;
	strcpy(io_volume, vol);
	return 0;
}

int CodeBlock::setCodeVolume(char* vol)
{
	code_volume = new char[strlen(vol)+1];
	if(code_volume == NULL)
		return -1;
	strcpy(code_volume, vol);
	return 0;
}

//*******************************************************//
CodeBlock::~CodeBlock()
{
	if(code != NULL)
	{
		delete [] code;
		code = NULL;
	}
	if(file_name != NULL)
	{
		delete [] file_name;
		file_name = NULL;
	}
	if(io_volume != NULL)
	{
		delete [] io_volume;
		io_volume = NULL;
	}
	if(code_volume != NULL)
	{
		delete [] code_volume;
		code_volume = NULL;
	}
}

CodeBlock::CodeBlock(const CodeBlock& _cb)
{
	if(_cb.code != NULL)
	{
		code = new char[strlen(_cb.code)+1];
		strcpy(code, _cb.code);
	}
	if(file_name != NULL)
	{
		file_name = new char[strlen(_cb.file_name)+1];
		strcpy(file_name, _cb.file_name);
	}
	if(io_volume != NULL)
	{
		io_volume = new char[strlen(_cb.io_volume)+1];
		strcpy(io_volume, _cb.io_volume);
	}
	if(code_volume != NULL)
	{
		code_volume = new char[strlen(_cb.code_volume)+1];
		strcpy(code_volume, _cb.code_volume);
	}
}

CodeBlock& CodeBlock::operator=(const CodeBlock& _cb)
{
	if (this != &_cb)
	{
		if (code != NULL)
			delete [] code;
		if (_cb.code != NULL)
		{
			code = new char[strlen(_cb.code)+1];
			strcpy(code, _cb.code);
		}
		else
			code = NULL;
		if (file_name != NULL)
			delete [] file_name;
		if (_cb.file_name != NULL)
		{
			file_name = new char[strlen(_cb.file_name)+1];
			strcpy(file_name, _cb.file_name);
		}
		else
			file_name = NULL;
		if (io_volume != NULL)
			delete [] io_volume;
		if (_cb.io_volume != NULL)
		{
			io_volume = new char[strlen(_cb.io_volume)+1];
			strcpy(io_volume, _cb.io_volume);
		}
		else
			io_volume = NULL;
		if (code_volume != NULL)
			delete [] code_volume;
		if (_cb.code_volume != NULL)
		{
			code_volume = new char[strlen(_cb.code_volume)+1];
			strcpy(code_volume, _cb.code_volume);
		}
		else
			code_volume = NULL;
	}
	return *this;
}

CodeBlock* CodeBlock::copy()
{
	CodeBlock* tmp = new CodeBlock();
	*tmp = *this;
	return tmp;
}
//*******************************************************//

}

#endif //__FRIGATE_CODE_BLOCK_CPP__

