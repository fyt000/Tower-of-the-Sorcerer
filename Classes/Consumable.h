#pragma once
#include "MyEvent.h"

class Consumable :
	public MyEvent
{
public:
	Consumable(int imageIdx, const std::string& decription, int hp, int atk, int def, int gold);
	bool triggerEvent();
	virtual ~Consumable();
	Consumable* clone();

private:
	int hp;
	int atk;
	int def;
	int gold;
};
