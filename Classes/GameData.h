#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include <vector>
#include "HeroX.h"
#include "Key.h"
#include "GlobalDefs.h"


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
	const static int MAXFLOOR=2;
	int goUpStairs();
	int goDownStairs();
	int setFloor(int);
	cocos2d::Sprite* getSprite(int x,int y);
	void moveHero(std::pair<int,int>);
	void killEvent(std::pair<int,int> place);
	void moveHeroFinalStep(std::pair<int,int> dest);
	PATH pathFind(std::pair<int,int> dest);
	PATH pathFind(int dx,int dy);
	void log(std::string message,bool instant=true);
	void showLog();
	HeroX hero;
	cocos2d::EventListenerTouchAllAtOnce* floorMouseListener;
	
	//all the display labels... location set at FloorScene
	cocos2d::Label* logLabel;
	LabelBinder<int> floor;

private:
	MyEvent* getEventData(int id);
	MyEvent* getEventData(int x,int y);
	MyEvent* EVENTDATA[MAXEVENT]={NULL};
	int FLOOREVENTS[MAXFLOOR][11][11]={0}; //int representation - read from config?
	MyEvent* FloorEvents[MAXFLOOR][11][11]={NULL}; //the actual objects
	void loadFloor();
	GameData();
	~GameData();
};

