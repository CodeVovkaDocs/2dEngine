#pragma once
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "Object.h"

#include <vector>
#include <string>

class IComponentContainer
{
public:
	static unsigned int componentCount;
	virtual  ~IComponentContainer() {};
	virtual void Delete(object obj) = 0;
	virtual bool Check(object obj) = 0;
};

unsigned int IComponentContainer::componentCount = 0;

template<typename ComponentT>
class ComponentContainer :public IComponentContainer
{
public:

	static unsigned int count;
	
	ComponentContainer()
	{
		componentCount++;
		count = componentCount;
		currentObjectCount = MIN_OBJECTS;
		ObjectToIndexRegistry.resize(currentObjectCount);
		IndexToObjectRegistry.resize(currentObjectCount);
	}

	void Add(object obj, ComponentT component)
	{
		
		if (obj > currentObjectCount -1)
		{
			currentObjectCount += (obj - currentObjectCount +1);
			ObjectToIndexRegistry.resize(currentObjectCount);
			IndexToObjectRegistry.resize(currentObjectCount);
		}
		if (ObjectToIndexRegistry[obj] == 0)
		{
			ComponentData.push_back(component);
			ObjectToIndexRegistry[obj] = ComponentData.size() - 1;
			IndexToObjectRegistry[ComponentData.size() - 1] = obj;
		}
	}

	void Delete(object obj)
	{
		if (ComponentData.size() > 0)
		{
			ComponentData.at(ObjectToIndexRegistry[obj]) = ComponentData.back();

			IndexToObjectRegistry[ObjectToIndexRegistry[obj]] = IndexToObjectRegistry[ComponentData.size() - 1];
			ObjectToIndexRegistry[IndexToObjectRegistry[ComponentData.size() - 1]] = ObjectToIndexRegistry[obj];

			ObjectToIndexRegistry[obj] = 0;
			IndexToObjectRegistry[ComponentData.size() - 1] = 0;

			ComponentData.pop_back();
		}
	}

	bool Check(object obj)
	{
		if (ObjectToIndexRegistry[obj] != 0)
		{
			return true;
		}
		return false;
	}


	ComponentT& Get(object obj)
	{
		return ComponentData[ObjectToIndexRegistry[obj]];
	}

	int GetSize()
	{
		return ComponentData.size();
	}

	ComponentT& GetData(int i)
	{
		return ComponentData[i];
	}

	object GetObject(int index)
	{
		return IndexToObjectRegistry[index];
	}
	
private:

	std::vector<ComponentT> ComponentData;
	std::vector<object> ObjectToIndexRegistry;
	std::vector<int> IndexToObjectRegistry;

	unsigned int currentObjectCount;
};

template<typename ComponentT>
unsigned int ComponentContainer<ComponentT>::count;

#endif // !DATA_MANAGER_H

