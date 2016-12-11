#pragma once
#include "MyEvent.h"

class Configureader{
public:
	static bool ReadEventData(MyEvent**,int maxEvent);
	static bool ReadFloorEvents(int FloorArr[][11][11],int maxFloor,int maxx,int maxy);
};
