#include "Door.h"
#include "GameData.h"
#include "DialogStruct.h"
#include <queue>


Door::Door(int imageIdx,std::string desc,KeyType doorType):MyEvent(imageIdx,desc),doorType(doorType)
{
}

bool Door::triggerEvent()
{
	/*
	std::queue<DialogStruct> dialogs;
	dialogs.emplace(DialogStruct("lets talk for a while1",DIALOGTYPE::NONE));
	dialogs.emplace(DialogStruct("lets talk for a while2",DIALOGTYPE::NONE));
	dialogs.emplace(DialogStruct("lets talk for a while3",DIALOGTYPE::NONE));
	dialogs.emplace(DialogStruct("say yes or no",DIALOGTYPE::YN));
	GameData::getInstance()->showDialog(dialogs,[this](int choice)->void{
		selfDestruct();
	});
	return false;
	*/
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
