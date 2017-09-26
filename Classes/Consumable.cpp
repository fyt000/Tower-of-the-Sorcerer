#include "Consumable.h"
#include "LabelBinder.h"
#include "GameData.h"
#include <string>
#include "MyAction.h"

//no use for gold...yet..maybe not
Consumable::Consumable(int imageIdx, const std::string& desc, int hp, int atk, int def, int gold) :
	MyEvent(imageIdx, desc), hp(hp), atk(atk), def(def), gold(gold)
{
}

bool Consumable::triggerEvent()
{
	FlatStat flatStat(nullptr, getDescription(), hp, atk, def, gold);
	flatStat.perform(nullptr);
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
