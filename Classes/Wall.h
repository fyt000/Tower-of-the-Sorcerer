#pragma once
#include "MyEvent.h"

class Wall:
	public MyEvent
{
public:
	Wall(int imageIdx,std::string desc);
	bool triggerEvent();
	Wall* clone();
	~Wall();
};