#pragma once
#include "Enemy.h"
#include "MyEvent.h"

class GameData
{
private:
	GameData();
	~GameData();

public:
	static GameData* getInstance();
	MyEvent* getEventData(int id);
	const int height =500;
	const int width =800;

private:
	MyEvent* EVENTDATA[500]={NULL};
};

