#include "Consumable.h"
#include "LabelBinder.h"
#include "GameData.h"
#include <string>
#include <sstream>

//no use for gold...yet..maybe not
Consumable::Consumable(int imageIdx,std::string desc,int hp,int atk,int def,int gold):
	MyEvent(imageIdx,desc),hp(hp),atk(atk),def(def),gold(gold)
{
}

bool Consumable::triggerEvent()
{
	std::stringstream msgBuilder;
	std::string msg=GStr("consume");
	std::string hpStr;
	std::string atkStr;
	std::string defStr;
	if (hp!=0){
		hpStr=stdsprintf(GStr("hp_change"),hp);
		GameData::getInstance()->hero->hp.addVal(hp);
	}
	if (atk!=0){
		hpStr=stdsprintf(GStr("atk_change"),atk);
		GameData::getInstance()->hero->atk.addVal(atk);
	}
	if (def!=0){
		hpStr=stdsprintf(GStr("def_change"),def);
		GameData::getInstance()->hero->def.addVal(def);
	}
	GameData::getInstance()->log(stdsprintf(msg,getDescription(),hpStr,atkStr,defStr));
	selfDestruct();
	return true;
}

Consumable::~Consumable()
{
}

Consumable * Consumable::clone()
{
	return new Consumable(*this);
}
