#pragma once
#include "Event.h"



class IEventHandler
{
public:

	virtual ~IEventHandler() {};
	virtual void Handle(Event* event) = 0;
};


template <class T>
class EventHandler : public IEventHandler
{
public:
	
	EventHandler(T* callbackObject, void (T::*callback)(Event* event))
	{
		this->callbackObject = callbackObject;
		this->callback = callback;
	}

	void Handle(Event* event)
	{
		(callbackObject->*callback)(event);
	}

private:

	T* callbackObject;
	void (T::*callback)(Event* event);

};