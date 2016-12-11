#include "Door.h"
#include "GameData.h"



Door::Door(int imageIdx,std::string desc,KeyType doorType):MyEvent(imageIdx,desc),doorType(doorType)
{
}

bool Door::triggerEvent()
{
	if (GameData::getInstance()->hero.keys[doorType]->V() >= 1){
		GameData::getInstance()->hero.keys[doorType]->subVal(1);
		GameData::getInstance()->log("opened a door");
		selfDestruct();
		return true;
	}
	else{
		GameData::getInstance()->log("you don't have the key to open the door");
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
