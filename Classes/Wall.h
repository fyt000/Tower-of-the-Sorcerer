#pragma once
#include "MyEvent.h"

class Wall:
	public MyEvent
{
public:
	Wall(int id,std::string desc);
	bool triggerEvent();
	Wall* clone();
	~Wall();
};