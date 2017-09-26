#pragma once
#include "MyEvent.h"

class Stairs :
	public MyEvent
{
public:
	Stairs(int imageIdx, const std::string& desc, int targetFloor, int x, int y, twsutil::DIR);
	bool triggerEvent();
	virtual ~Stairs();
	Stairs* clone();
	int getTargetFloor();

private:
	int targetFloor;
	int tx;
	int ty;
	twsutil::DIR heroDir;
};