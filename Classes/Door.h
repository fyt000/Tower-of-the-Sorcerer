#pragma once
#include "MyEvent.h"


class Door:
	public MyEvent
{
public:
	Door(int id,std::string desc,enum KeyType doorType);
	bool triggerEvent();
	virtual ~Door();
	Door* clone();

private:
	enum KeyType doorType;

};

