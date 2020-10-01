#pragma once
#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include "Object.h"
#include <array>

#define MAX_OBJECTS 1024
#define MAX_COMPONENTS 128
#define MAX_COMPONENT_SIZE 254

using byte_data = char[MAX_COMPONENT_SIZE];




class ObjectData
{

public:

	ObjectData()
	{
		data = new byte_data*[MAX_OBJECTS];

		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			data[i] = new byte_data[MAX_OBJECTS];
		}
	}


	template<typename T>
	bool AddComponent(int i, int j, T component)
	{
		if (sizeof(T) <= MAX_COMPONENT_SIZE)
		{
			memcpy(data[i][j], &component, sizeof(T));

			std::cout << "Element added" << "\n";

			return true;
		}

		std::cout << "Size exeeded" << "\n";
		
		return false;
	}

	template<typename T>
	bool GetComponent(int i, int j, T *component)
	{
		if (sizeof(T) <= MAX_COMPONENT_SIZE)
		{
			memcpy(component, data[i][j], sizeof(T));

			std::cout << "Element returned" << "\n";

			return true;
		}

		std::cout << "Return size mismatch" << "\n";

		return false;
	}


private:

	byte_data** data;

};



#endif // !OBJECT_DATA_H

