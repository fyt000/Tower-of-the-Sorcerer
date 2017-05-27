#pragma once
//stuff that might change in a fight - TBH only hp changes, but just in case
struct FightableSnapshot {
	int atk;
	int def;
	int hp;
	FightableSnapshot(int hp, int atk, int def) :hp(hp), atk(atk), def(def) {}
};