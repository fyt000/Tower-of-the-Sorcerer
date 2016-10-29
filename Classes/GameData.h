#pragma once
#include "Enemy.h"
#include "MyEvent.h"
#include "cocos2d.h"
#include <vector>

class GameData
{
private:
	GameData();
	~GameData();

public:
	static GameData* getInstance();
	MyEvent* getEventData(int id);
	MyEvent* getEventData(int x,int y);
	const int height =500;
	const int width =800;
	int goUpStairs();
	int goDownStairs();
	int setFloor(int);
	cocos2d::Sprite* getSprite(int x,int y,int px,int py);
	std::vector<std::pair<int,int>> pathFind(std::pair<int,int> dest);
	std::vector<std::pair<int,int> > pathFind(int dx,int dy);

private:
	MyEvent* EVENTDATA[500]={NULL};
	int FLOOREVENTS[2][11][11];
	int floor=1;
	int heroX=0;
	int heroY=0;
};

