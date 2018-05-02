#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include <vector>
#include "HeroX.h"
#include "Key.h"
#include "GlobalDefs.h"
#include "FloorScene.h"
#include "DialogStruct.h"
#include <mutex>
#include "Enemy.h"
#include "HeroItem.h"
#include "Stairs.h"
#include "GlobalEvent.h"
#include <list>
#include <deque>
#include <memory>
#include "GameState.h"

//mostly handle the logic
//Hero class handles the rest
//Doesn't handle the graphics...
//animation are handle by each MyEvent
//and set at FloorScene
class GameData
{
public:
	std::unique_ptr<HeroX> hero;
	std::unique_ptr<LabelBinder<int>> keys[KeyType::LAST]; //3 types of keys - each key will be the same type
	//TODO investigate why this was here
	cocos2d::EventListenerTouchAllAtOnce* floorMouseListener;

	//all the display labels... location set at FloorScene
	cocos2d::Label* logLabel;
	std::unique_ptr<LabelBinder<int>> floor;
	FloorScene* flScn;

	//enemy info display
	cocos2d::Label* eDescLabel;
	cocos2d::Label* eHpLabel;
	cocos2d::Label* eAtkLabel;
	cocos2d::Label* eDefLabel;

	static GameData& getInstance(int saveRec);
	static GameData& getInstance();
	std::shared_ptr<MyEvent> getEvent(int x, int y);

	int setFloor(int f);
	cocos2d::Sprite* getSprite(int x, int y);
	void moveHero(std::pair<int, int>);
	void moveHero(twsutil::DIR dir);
	void killEvent(std::pair<int, int> place);
	//f==-1 for cur floor
	//note that setEvent DO NOT call delete on the current event occupying x,y
	void setEvent(int id, int x, int y, int f = -1);
	twsutil::PATH pathFind(std::pair<int, int> dest);
	twsutil::PATH pathFind(int dx, int dy);
	void log(const std::string& message, bool instant = true);
	void showLog();

	//dialog
	void showDialog(std::queue<DialogStruct>& dq, std::function<void(int)> callback);
	void showDialog(const DialogStruct& ds, std::function<void(int)> callback);
	void dialogCompleted(int choice); //used by FloorScene, call callback if any

	// this is for keyboard
	void continousMovement();
	// this is for mouse
	void nextStep();

	void finalMovementCleanup(bool cont = true);

	void gameover(bool dialog = true);
	void saveGame(int saveRec);

	void attachEnemyInfo(Fightable* enemy);

	//items
	void obtainItem(int idx);
	//item 1
	void showFloorEnemyStats();
	//item 2
	bool fastStairs();
	//item 3
	void replayDialog();

	// block() on event start and releaseBlock() on event end
	// to potentially unblock
	// this allows nested events to keep blocking the input
	void block();
	void releaseBlock();
	bool isBlocked();


	int getEventID(int floor, int x, int y);

	void triggerGlobalEvents();

private:

	bool newGame = true;
	bool floorChange = false;
	std::shared_ptr<Stairs> upstair = nullptr;
	std::shared_ptr<Stairs> downstair = nullptr;
	int blockCounter = 0;
	bool blocked = false;

	std::queue<DialogStruct> dialogQ;
	std::queue<std::function<void(int)> > dialogCallbackQ; //probably need a queue as well

	twsutil::PATH heroMovementPath;

	// the actual objects
	std::unique_ptr<HeroItem> items[twsutil::MAXITEMS] = { 0 };
	std::list<std::unique_ptr<GlobalEvent>> GLOBALEVENT[twsutil::MAXFLOOR + 1];
	std::shared_ptr<MyEvent> FloorEvents[11][11] = { { 0 } }; //the actual objects

	GameState state;

	
	std::unique_ptr<MyEvent> getEventData(int id);
	std::unique_ptr<MyEvent> getEventData(int x, int y);

	void loadFloor(int);
	
	void initWithState();
	void defaultInit();
	//what do I need to save?
	//if a new game
	//TODO copy gamedata.json and res_english.json -> so game update won't obsolete old saves
	//save hero stats: hp, atk, def, gold, x, y
	//save shop use stats: 
	//save global event... iterate the list, save the ids, when loading, only load the ones that match the saved id
	//save Floorevents, just do a dump
	//save HeroItem, the id and the number of uses

	GameData();
	GameData(int saveRec);
	~GameData();
};
