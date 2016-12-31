#pragma once
#include <string>
#include "cocos2d.h"
#include "MyAction.h"

class MyEvent
{
public:
	MyEvent(int imageIdx,const std::string& decription);
	MyEvent(int imageIdx,const std::string& decription,int imageIdx2);
	virtual MyEvent* clone();
	virtual ~MyEvent(); 
	void setXY(int x,int y);

	//virtual bool isEnemy();
	virtual bool canAtk();
	std::string getDescription();
	virtual cocos2d::Sprite* getSprite(bool createNew=false);
	virtual bool triggerEvent();
	virtual bool stepOnEvent();
	int getX();
	int getY();
	void attachAction(MyAction*);
	int performActions();
	cocos2d::Sprite* sprite=nullptr;

protected:
	int imageIdx;
	int imageIdx2=-1;
	int x;
	int y;
	
	void selfDestruct();


private:
	std::string description;
	std::vector<MyAction*> actions;
	/*
	std::string imageName1;
	std::string imageName2;
	std::string description;
	int interactive; //0 - no, 1 - mob(fight), 2 - npc(dialog), 3 - store(?)
	bool passable;
	*/
};

