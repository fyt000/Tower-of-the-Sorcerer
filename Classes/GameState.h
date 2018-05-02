#pragma once
#include "GlobalDefs.h"
#include <unordered_set>
#include <string>
#include <fstream>
#include "cocos2d.h"

// everything that needs to go into save
struct GameState {
	int ITEMS[twsutil::MAXITEMS] = { 0 };
	int FLOOREVENTS[twsutil::MAXFLOOR + 1][11][11] = { { { 0 } } }; //int representation - read from config?
	std::unordered_set<int> globalEvt;
	int keys[3];

	// NOT THE LATEST
	int heroHP;
	int heroAtk;
	int heroDef;
	int heroGold;
	int heroX;
	int heroY;
	int heroFloor;
	int shopUses;

	// other stuff like special shield etc.

	void serializeTo(int saveRec) {
		auto path = persistentPath(saveRec);
		CCLOG("saving %s", path.c_str());
		std::ofstream out(path, std::ofstream::binary);
		// there might be paddings, so dump each item
		CCLOG("%d", sizeof(ITEMS));
		out.write((const char*)ITEMS, sizeof(ITEMS));
		CCLOG("%d", sizeof(FLOOREVENTS));
		out.write((const char*)FLOOREVENTS, sizeof(FLOOREVENTS));
		out.write((const char*)keys, sizeof(keys));
		out.write((const char*)&heroHP, sizeof(heroHP));
		out.write((const char*)&heroAtk, sizeof(heroAtk));
		out.write((const char*)&heroDef, sizeof(heroDef));
		out.write((const char*)&heroGold, sizeof(heroGold));
		out.write((const char*)&heroX, sizeof(heroX));
		out.write((const char*)&heroY, sizeof(heroY));
		out.write((const char*)&heroFloor, sizeof(heroFloor));
		out.write((const char*)&shopUses, sizeof(shopUses));
		// write length, altho size can be inferred
		auto size = globalEvt.size();
		out.write((const char*)&size, sizeof(size));
		for (auto evtId : globalEvt) {
			out.write((char*)evtId, sizeof(evtId));
		}
	}
	bool deserializeFrom(int saveRec) {
		auto path = persistentPath(saveRec);
		CCLOG("loading %s", path.c_str());
		std::ifstream input(path, std::ifstream::binary);
		if (!input.good()) return false;

		input.read((char*)ITEMS, sizeof(ITEMS));
		input.read((char*)FLOOREVENTS, sizeof(FLOOREVENTS));
		input.read((char*)keys, sizeof(keys));
		input.read((char*)&heroHP, sizeof(heroHP));
		input.read((char*)&heroAtk, sizeof(heroAtk));
		input.read((char*)&heroDef, sizeof(heroDef));
		input.read((char*)&heroGold, sizeof(heroGold));
		input.read((char*)&heroX, sizeof(heroX));
		input.read((char*)&heroY, sizeof(heroY));
		input.read((char*)&heroFloor, sizeof(heroFloor));
		input.read((char*)&shopUses, sizeof(shopUses));
		decltype(globalEvt.size()) size = 0;
		input.read((char*)&size, sizeof(size));
		for (size_t i = 0; i < size; i++) {
			int evt = 0;
			input.read((char*)&evt, sizeof(evt));
			globalEvt.insert(evt);
		}
		return true;
	}
private:
	std::string persistentPath(int saveRec) {
		return cocos2d::FileUtils::getInstance()->getWritablePath() + std::to_string(saveRec) + ".sav";
	}
};