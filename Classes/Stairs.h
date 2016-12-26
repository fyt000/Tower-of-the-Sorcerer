#pragma once
#include "MyEvent.h"

class Stairs:
	public MyEvent
{
public:
	Stairs(int imageIdx,std::string desc,int targetFloor,int x,int y,enum DIR);
	bool triggerEvent();
	virtual ~Stairs();
	Stairs* clone();
	int getTargetFloor();

private:
	int targetFloor;
	int tx;
	int ty;
	enum DIR heroDir;
};