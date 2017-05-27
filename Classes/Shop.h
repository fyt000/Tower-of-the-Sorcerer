#pragma once
#include "MyEvent.h"


class Shop : public MyEvent {
public:
	Shop(int imageIdx, const std::string& desc, int imageIdx2, int baseHP, int baseAtk, int baseDef);
	bool triggerEvent();
	virtual ~Shop();
	Shop* clone();
	static int shopUses; //read from save file
private:
	int baseHP;
	int baseAtk;
	int baseDef;
};