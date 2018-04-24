#include "Enemy.h"
#include "GlobalDefs.h"
#include "TransformCoordinate.h"
#include "GameData.h"

USING_NS_CC;
using namespace twsutil;

Enemy::Enemy(int imageIdx, const std::string& desc, int secondImageID, int hp, int atk, int def, int gold) :
	Fightable(imageIdx, desc, secondImageID, hp, atk, def, gold) {}


bool Enemy::triggerEvent()
{
	if (!attackable(GameData::getInstance().hero.get())) {
		GameData::getInstance().log(stdsprintf(std::string("%s is too strong."), getDescription()));
		return false;
	}
	return true;
}

bool Enemy::stepOnEvent()
{
	CCLOG("fighting enemy");
	bool fightR = Fightable::stepOnEvent();
	if (fightR) {
		GameData::getInstance().hero->gold.addVal(gold.V());
		GameData::getInstance().log(stdsprintf(GStr("beat_enemy"), getDescription(), gold.V()), false);
	}

	return fightR;
}


Enemy::~Enemy() {
}
