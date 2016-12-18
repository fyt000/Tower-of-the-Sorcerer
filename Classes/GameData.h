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

const int MAXEVENT=500;

//mostly handle the logic
//Hero class handles the rest
//Doesn't handle the graphics...
//animation are handle by each MyEvent
//and set at FloorScene
class GameData
{
public:
	static GameData* getInstance();
	MyEvent* getEvent(int x,int y);
	const static int MAXFLOOR=3;

	int setFloor(int f);
	cocos2d::Sprite* getSprite(int x,int y);
	void moveHero(std::pair<int,int>);
	void killEvent(std::pair<int,int> place);
	//f==-1 for cur floor
	//note that setEvent DO NOT call delete on the current event occupying x,y
	void setEvent(int id,int x,int y,int f=-1);
	void moveHeroFinalStep(std::pair<int,int> dest);
	PATH pathFind(std::pair<int,int> dest);
	PATH pathFind(int dx,int dy);
	void log(std::string& message,bool instant=true);
	void showLog();
	HeroX* hero;
	cocos2d::EventListenerTouchAllAtOnce* floorMouseListener;
	
	//all the display labels... location set at FloorScene
	cocos2d::Label* logLabel;
	LabelBinder<int>* floor;
	FloorScene* flScn;

	//enemy info display
	cocos2d::Label* eDescLabel;
	cocos2d::Label* eHpLabel;
	cocos2d::Label* eAtkLabel;
	cocos2d::Label* eDefLabel;
	

	//dialog
	void showDialog(std::queue<DialogStruct>& dq,std::function<void(int)> callback);
	void showDialog(DialogStruct& ds,std::function<void(int)> callback);
	void dialogCompleted(int choice); //used by FloorScene, call callback if any

	void init();
	void gameover();

	void addToFree(MyEvent*);
	void freePendingFreeList();

	void attachEnemyInfo(Enemy* enemy);

private:
	//now, do I need a lock.... I have no idea how cocos2dx works here
	//adding a lock for safety concerns
	std::mutex freeListLock;
	std::vector<MyEvent*> pendingFreeList;
	MyEvent* getEventData(int id);
	MyEvent* getEventData(int x,int y);
	MyEvent* EVENTDATA[MAXEVENT]={NULL};
	int FLOOREVENTS[MAXFLOOR][11][11]={0}; //int representation - read from config?
	MyEvent* FloorEvents[11][11]={NULL}; //the actual objects
	void loadFloor(int);
	bool floorChange=false;
	
	std::queue<DialogStruct> dialogQ;
	std::function<void(int)> dialogCallback;


	GameData();
	~GameData();
};

