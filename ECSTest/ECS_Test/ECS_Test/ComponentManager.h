#pragma once
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "ComponentContainer.h"
#include <iostream>
#include <typeindex>
#include <map>

template<typename ComponentT>
std::type_index GetId()
{
	return std::type_index(typeid(ComponentT));
}

template<typename ComponentT>
struct Id
{
	 std::type_index id = GetId<ComponentT>();
};


class ComponentManager
{
public:

	template<typename ComponentT>
	void RegisterComponent()
	{
		Id<ComponentT> i;
		data.push_back(new ComponentContainer<ComponentT>());
		std::cout << i.id.name() << " Registered\n";
		std::cout << ComponentContainer<ComponentT>::componentCount << "\n";
	}

	template<typename ComponentT>
	void AddComponent(object obj, ComponentT component)
	{
		GetComponentArray<ComponentT>()->Add(obj, component);
	}

	template<typename ComponentT>
	void DeleteComponent(object obj)
	{
		GetComponentArray<ComponentT>()->Delete(obj);
	}

	template<typename ComponentT>
	bool CheckComponent(object obj)
	{
		return GetComponentArray<ComponentT>()->Check(obj);
	}



	template<typename ComponentT>
	ComponentT& GetComponent(object obj)
	{

		return GetComponentArray<ComponentT>()->Get(obj);
	}

	template<typename ComponentT>
	int GetArraySize()
	{
		return GetComponentArray<ComponentT>()->GetSize();
	}

	template<typename ComponentT>
	ComponentT& GetArrayData(int i)
	{
		return GetComponentArray<ComponentT>()->GetData(i);
	}

	template<typename ComponentT>
	object GetObject(int index)
	{
		return GetComponentArray<ComponentT>()->GetObject(index);
	}

	void DeleteAllObjectData(object obj)
	{
		for (auto itr = data.begin(); itr != data.end(); ++itr)
		{
			if ((*itr)->Check(obj))
			{
				(*itr)->Delete(obj);
			}
		}
	}
	
private:

	std::vector<IComponentContainer*> data;

	template<typename ComponentT>
	ComponentContainer<ComponentT>* GetComponentArray()
	{
		return static_cast<ComponentContainer<ComponentT>*>(data[ComponentContainer<ComponentT>::count -1]);
	}


};
#endif // !OBJECT_MANAGER_H
