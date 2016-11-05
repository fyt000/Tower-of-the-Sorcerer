#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include <vector>
#include "HeroX.h"
#include "GlobalDefs.h"


class GameData
{
private:
	GameData();
	~GameData();

public:
	static GameData* getInstance();
	MyEvent* getEvent(int x,int y);
	const static int MAXFLOOR=2;
	int goUpStairs();
	int goDownStairs();
	int setFloor(int);
	cocos2d::Sprite* getSprite(int x,int y);
	//void moveHero(enum DIR direction);
	void moveHero(PATH path);
	void moveHero(std::pair<int,int>);
	void moveHeroFinalStep(std::pair<int,int> dest);
	PATH pathFind(std::pair<int,int> dest);
	PATH pathFind(int dx,int dy);
	HeroX hero;
	EventListenerTouchAllAtOnce* floorMouseListener;

private:
	MyEvent* getEventData(int id);
	MyEvent* getEventData(int x,int y);
	MyEvent* EVENTDATA[500]={NULL};
	int FLOOREVENTS[MAXFLOOR][11][11]; //int representation - read from config?
	MyEvent* FloorEvents[MAXFLOOR][11][11]; //the actual objects
	void loadFloor();
	int floor=1;
	
	
};

