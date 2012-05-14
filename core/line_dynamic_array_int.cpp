#ifndef __LINE_DYNAMIC_ARRAY_INT_CPP__
#define __LINE_DYNAMIC_ARRAY_INT_CPP__

#include "line_dynamic_array.h"

#ifndef INTERNAL_ARRAY_ALONGATION_SIZE
	#define INTERNAL_ARRAY_ALONGATION_SIZE 2048
#endif

/******************************************************************************/
int Line_dynamic_array<int>::add_element(int element)
{
	if(num_records==current_internal_array_size)
	{
		int *new_array=NULL;

		int new_array_size=current_internal_array_size+
		INTERNAL_ARRAY_ALONGATION_SIZE;

		new_array=(int *)realloc(data,new_array_size*sizeof(int));
		if(new_array==NULL)
		{
			return LINE_DYNAMIC_ARRAY_ERROR;
		}

		data=new_array;
		current_internal_array_size=new_array_size;
	}

	int new_element=element;

	data[num_records]=new_element;
	num_records++;

	return LINE_DYNAMIC_ARRAY_SUCCESS;
}
/******************************************************************************/
int Line_dynamic_array<int>::get_elem(int position)
{
	if((position<0) || (position>=num_records))
	{
		return -1;
	}

	return data[position];
}
/******************************************************************************/
int Line_dynamic_array<int>::vacuum(void)
{
	if(num_records==0)
	{
		if(data!=NULL)
		{
			free(data);
			data=NULL;
		}

		current_internal_array_size=0;
		return 0;
	}

	if(current_internal_array_size>num_records)
	{

		int* new_data=(int*)realloc
		(
			data,
			num_records*sizeof(int)
		);

		if(new_data==NULL)
		{
			return -1;
		}

		data=new_data;
	}

	return 0;
}
/******************************************************************************/
Line_dynamic_array<int>::~Line_dynamic_array()
{
	if(data != NULL)
	{
		free(data);
		data = NULL;
	}
	num_records=0;
	current_internal_array_size=0;
	return;
}
/******************************************************************************/
Line_dynamic_array<int>::Line_dynamic_array(const Line_dynamic_array<int>& arr)
{
	if(data != NULL)
	{
		free(data);
		data = NULL;
	}
	num_records = arr.num_records;
	current_internal_array_size = arr.current_internal_array_size;
	data = (int *)malloc(arr.current_internal_array_size*sizeof(int));
	for(int i = 0; i<num_records; ++i)
	{
		data[i]=arr.data[i];
	}
}
/******************************************************************************/
int* Line_dynamic_array<int>::look_position(int position)
{
	if((position<0) || (position>=num_records))
	{
		return NULL;
	}

	return &(data[position]);
}
/******************************************************************************/
int Line_dynamic_array<int>::find_element(int pattern)
{
	int i;
	for(i=0;i<num_records;i++)
	{
		if(data[i] == pattern)
		{
			return 1;
		}
	}
	return 0;
}
/******************************************************************************/
int  Line_dynamic_array<int>::delete_element(int position)
{
	if((position<0)||(position>=num_records))
	{
		return -1;
	}

	num_records--;
	for(int i=position ; i<num_records ; i++)
	{
		data[i]=data[i+1];
	}

	return 0;
}
/******************************************************************************/
int  Line_dynamic_array<int>::print(void)
{
	printf("Line_dynamic_array content:\n\n");

	for(int i=0;i<num_records;i++)
	{
		printf("%d",data[i]);
		printf("\n");
	}

	return 0;
}
/******************************************************************************/
void Line_dynamic_array<int>::erase()
{
	if(data != NULL)
	{
		free(data);
		data = NULL;
	}
	num_records=0;
	current_internal_array_size=0;
	return;
}

#endif //__LINE_DYNAMIC_ARRAY_INT_CPP__

