#include "Shop.h"
#include "GameData.h"
#include "GlobalDefs.h"

using namespace twsutil;

int Shop::shopUses = 0;

Shop::Shop(int imageIdx, const std::string& desc, int imageIdx2, int baseHP, int baseAtk, int baseDef) :
	MyEvent(imageIdx, desc, imageIdx2), baseHP(baseHP), baseAtk(baseAtk), baseDef(baseDef) {
}

bool Shop::triggerEvent() {
	int multplier = 1; //I think there is a upper limit, but I don't remember the number
	for (int i = 1; i <= shopUses; i++)
		multplier *= 2;
	int goldCost = multplier * 20;
	GameData::getInstance().showDialog(DialogStruct(stdsprintf(GStr("shop"), goldCost), DIALOGTYPE::LIST,
	{ stdsprintf(GStr("shop_hp"),baseHP),stdsprintf(GStr("shop_atk"),baseAtk),stdsprintf(GStr("shop_def"),baseDef),GStr("cancel") }),
		[this, goldCost](int choice) {
		if (choice == 3) //cancel
			return;
		if (GameData::getInstance().hero->spendGold(goldCost)) {
			if (choice == 0)
				GameData::getInstance().hero->hp.addVal(baseHP);
			else if (choice == 1)
				GameData::getInstance().hero->atk.addVal(baseAtk);
			else if (choice == 2)
				GameData::getInstance().hero->def.addVal(baseDef);
		}
		else {
			GameData::getInstance().log(GStr("not_enough_gold"));
		}
		Shop::shopUses++;
	});
	return false;
}

Shop::~Shop()
{
}