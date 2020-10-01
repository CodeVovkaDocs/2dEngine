#pragma once
#ifndef EVENT_SYSTEM
#define EVENT_SYSTEM


#include "Event.h"
#include "CollisionEvent.h"
#include "EventHandler.h"
#include <vector>
#include <map>
#include <queue>
#include <memory>
#include <iostream>


class EventSystem
{
public:

	template <class T,typename... Targs>
	void AddEvent(Targs...arg)
	{
		std::shared_ptr<Event> sharedPtr(new T(arg...));
		events.push(sharedPtr);
	}


	template <class T>
	void AddEventHandler(const char* eventId, T* callbackObjPtr, void (T::* callback)(Event* event))
	{
		IEventHandler* handler = new EventHandler<T>(callbackObjPtr, callback);
		handlers[eventId].push_back(handler);
	}

	void HandleEvents()
	{
		while (!events.empty())
		{
			if (handlers.find((*events.front()).GetId()) != handlers.end())
			{

				const char* eventId = (*events.front()).GetId();

				for (auto itr = handlers[eventId].begin(); itr != handlers[eventId].end(); ++itr)
				{
					(*itr)->Handle(&(*events.front()));
				}

			}

			events.pop();
		}
	}

private:

	std::queue<std::shared_ptr<Event>> events;
	std::map<const char*, std::vector<IEventHandler*>> handlers;
};


#endif // !EVENT_SYSTEM