#include "Stairs.h"
#include "GameData.h"

Stairs::Stairs(int imageIdx,std::string desc,int targetFloor,int x,int y,enum DIR dir):
	MyEvent(imageIdx,desc),targetFloor(targetFloor),tx(x),ty(y),heroDir(dir)
{
}

bool Stairs::triggerEvent()
{
	GameData::getInstance()->hero->getSprite()->stopAllActions(); //actually need to stop...
	int x=tx;int y=ty;enum DIR dir=heroDir; //setFloor will destruct this object and these fields will be unaccessible
	GameData::getInstance()->setFloor(targetFloor);
	//use the var saved on stack
	GameData::getInstance()->hero->setAbsPos(x,y,dir);
	return false;
}

Stairs::~Stairs()
{
}

Stairs * Stairs::clone()
{
	return new Stairs(*this);
}
