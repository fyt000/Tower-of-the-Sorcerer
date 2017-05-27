#include "Fightable.h"
#include "GameData.h"
#include "HeroX.h"
USING_NS_CC;

Fightable::Fightable(int imageIdx, const std::string& desc, int imageIdx2, int hp, int atk, int def, int gold) :MyEvent(imageIdx, desc, imageIdx2), hp(hp), atk(atk), def(def), gold(gold) {
}


int Fightable::hitBy(Fightable* hitter) {
	if (hitter->atk.V() - def.V() > 0)
		return hitter->atk.V() - def.V();
	return 0;
}

int Fightable::hit(Fightable* target) {
	return target->hitBy(this);
}

void Fightable::decHp(int amt)
{

	if (hp.V() - amt <= 0)
		hp.setVal(0);
	else
	{
		hp.subVal(amt);
	}
}

void Fightable::setLabelNofity(bool n)
{
	hp.setNofify(n);
	atk.setNofify(n);
	def.setNofify(n);
	gold.setNofify(n);
}

//change this to acoomodate items?
bool Fightable::attackable(HeroX *h)
{
	if (h->atk.V() > this->def.V())
		return true;
	return false;
}


//fight until the enemy is dead
//this method is implemented for Fight only because,
//IIRC, Zeno will engage the character (or some other Mob will)
//accept callback so that I'll return hp after each hit to the caller
int Fightable::fight(Fightable* target, std::function<void(Fightable&)> hpCallback1, std::function<void(Fightable&)> hpCallback2) {


	int totalDamageTaken = 0;

	//ok code is going in loops
	//add another loop here, refactor later
	//store the snapshots before fight and restore after fight...

	FightableSnapshot targetSS(target->getHp(), target->getAtk(), target->getDef());
	FightableSnapshot thisSS(getHp(), getAtk(), getDef());

	while (1) {
		int dmg = hit(target);
		target->decHp(dmg);
		if (hpCallback1 != nullptr)
			hpCallback1(*target);
		if (target->hp.V() <= 0)
			break;
		dmg = hitBy(target);
		decHp(dmg);
		if (hpCallback2 != nullptr)
			hpCallback2(*this);
		totalDamageTaken += dmg;
		if (hp.V() <= 0)
			break;
	}
	//do I need to disable notify? or is it already disabled
	target->hp.setVal(targetSS.hp);
	target->atk.setVal(targetSS.atk);
	target->def.setVal(targetSS.def);

	hp.setVal(thisSS.hp);
	atk.setVal(thisSS.atk);
	def.setVal(thisSS.def);

	return totalDamageTaken;
}

const int Fightable::getHp() {
	return hp.V();
}
const int Fightable::getAtk() {
	return atk.V();
}
const int Fightable::getDef() {
	return def.V();
}

bool Fightable::triggerEvent() {
	return true;
}

//think about extensions later... I don't care right now
bool Fightable::stepOnEvent() {

	GameData::getInstance()->attachEnemyInfo(this);
	GameData::getInstance()->hero->fightX(this,
		[](Fightable &f) { log("hp %d", f.getHp()); },
		[](Fightable &f) { log("hp %d", f.getHp()); });
	//GameData::getInstance()->killEvent(std::pair<int,int>(x,y));
	return true;
}

Fightable::~Fightable() {
}
