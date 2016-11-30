#include "Consumable.h"
#include "LabelBinder.h"
#include "GameData.h"
#include <string>
#include <sstream>

//no use for gold...yet..maybe not
Consumable::Consumable(int id,std::string desc,int hp,int atk,int def,int gold):
	MyEvent(id,desc),hp(hp),atk(atk),def(def),gold(gold)
{
}

bool Consumable::triggerEvent()
{
	std::stringstream msgBuilder;
	msgBuilder<<"Consumed "<<description<<". ";
	if (hp!=0){
		msgBuilder<<"Vitality increased by "<<hp;
		GameData::getInstance()->hero.hp.addVal(hp);
	}
	if (atk!=0){
		msgBuilder<<"Attack increased by "<<atk;
		GameData::getInstance()->hero.atk.addVal(atk);
	}
	if (def!=0){
		msgBuilder<<"Defense increased by "<<def;
		GameData::getInstance()->hero.def.addVal(def);
	}
	GameData::getInstance()->log(msgBuilder.str());
	GameData::getInstance()->killEvent(std::pair<int,int>(getX(),getY()));
	return true;
}

Consumable::~Consumable()
{
}

Consumable * Consumable::clone()
{
	return new Consumable(*this);
}
