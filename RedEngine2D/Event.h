#pragma once
class Event
{
public:
	virtual ~Event() {};
	virtual const char* GetId() = 0;
	//virtual void Erase() = 0;
};

