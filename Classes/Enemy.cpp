#include "Enemy.h"
#include "GlobalDefs.h"
#include "TransformCoordinate.h"
#include "GameData.h"

USING_NS_CC;

Enemy::Enemy(int imageIdx,std::string desc,int secondImageID,int hp,int atk,int def,int gold):
	Fightable(imageIdx,desc,secondImageID,hp,atk,def,gold){}


bool Enemy::canAtk(){
	return true;
}

bool Enemy::stepOnEvent()
{
	bool fightR = Fightable::stepOnEvent();
	//"Beat "+description+". Received "+ToString(gold.V())+" gold."
	if (fightR)
		GameData::getInstance()->log(stdsprintf(GStr("beat_enemy"),getDescription(),gold.V()),false);
	return fightR;
}


Enemy::~Enemy(){
}

Enemy * Enemy::clone()
{
	return new Enemy(*this);
}
