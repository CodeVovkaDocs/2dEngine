#pragma once
#ifndef OBJECT_MGR_H
#define OBJECT_MGR_H

#include "Object.h"
#include <queue>

class ObjectManager
{

public:

	ObjectManager()
	{
		lastObject = 0;
	}

	object NewObject()
	{
		object obj = 0;

		if (erasedObjects.size() > 0)
		{
			obj = erasedObjects.front();
			erasedObjects.pop();
		}
		else
		{
			obj = ++lastObject;
		}

		return obj;
	}

	void deleteObject(object obj)
	{
		erasedObjects.push(obj);
	}

private:

	object lastObject;
	std::queue<object> erasedObjects;
};


#endif // !OBJECT_MGR_H

