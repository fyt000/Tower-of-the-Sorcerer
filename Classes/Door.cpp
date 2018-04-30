#include "Door.h"
#include "GameData.h"
#include "DialogStruct.h"
#include "GlobalDefs.h"
#include <queue>
#include <string>

using namespace twsutil;

Door::Door(int imageIdx, const std::string& desc, KeyType doorType) :MyEvent(imageIdx, desc), doorType(doorType)
{
}

bool Door::triggerEvent()
{
	if (GameData::getInstance().keys[doorType]->V() >= 1) {
		GameData::getInstance().keys[doorType]->subVal(1);
		GameData::getInstance().log(stdsprintf(GStr("door_open"), GStr("key_" + std::to_string((int)doorType))));
		selfDestruct();
		return true;
	}
	else {
		GameData::getInstance().log(stdsprintf(GStr("door_nokey"), GStr("key_" + std::to_string((int)doorType))));
	}
	return false;
}

Door::~Door()
{
}

