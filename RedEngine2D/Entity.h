#pragma once
#ifndef ENTITY_HEADER
#define ENTITY_HEADER



#include "EntityComponent.h"
#include <map>
#include <iostream>



enum class entityState
{
	UNSET_STATE,
	IDLE,
	MOVING,
	MOVING_FAST,
	ATTACKING,
	DYING,
	DEAD
};



class Entity
{
public:

	Entity() {
		id = entityCount++;
		name = "UNSET";
		state = entityState::UNSET_STATE;
	}

	Entity(const char* name, entityState state) {
		id = entityCount++;
		this->name = name;
		this->state = state;
	}

	~Entity() {}

	int GetEntityCount() { return entityCount; }

	int GetEntityId() { return id; }

	const char* GetName() { return name; }

	entityState GetState() { return state; }

	void SetName(const char* name) { this->name = name; }

	void SetState(entityState state) { this->state = state; }

	void AddComponent(EntityComponent* component) { components[component->GetType()] = component; }


	template<class T>
	T* GetComponentPtr(entityComponentType componentType){

		if (components.find(componentType) != components.end())
		{
			return static_cast<T*>(components[componentType]);
		}

		return nullptr;
	}


	template<int N>
	bool CheckForComponents(const entityComponentType(&componentList)[N]){

		bool check = true;

		for (int i = 0; i < N; i++)
		{
			if (this->components.find(componentList[i]) == components.end())
			{
				check = false;
				break;
			}
		}

		return check;
	}

private:

	static int entityCount;

	int id;
	const char* name;
	entityState state;
	std::map<entityComponentType,EntityComponent*> components;

};



#endif // !ENTITY_HEADER

