#include "Door.h"
#include "GameData.h"



Door::Door(int imageIdx,std::string desc,KeyType doorType):MyEvent(imageIdx,desc),doorType(doorType)
{
}

bool Door::triggerEvent()
{
	if (GameData::getInstance()->hero.keys[doorType]->V() >= 1){
		GameData::getInstance()->hero.keys[doorType]->subVal(1);
		GameData::getInstance()->log(stdsprintf(GStr("door_open"),GStr("key_"+ToString((int)doorType))));
		selfDestruct();
		return true;
	}
	else{
		GameData::getInstance()->log(stdsprintf(GStr("door_nokey"),GStr("key_"+ToString((int)doorType))));
	}
	return false;
}

Door::~Door()
{
}

Door * Door::clone()
{
	return new Door(*this);
}
