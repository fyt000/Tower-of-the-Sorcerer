#pragma once
#include <string>
#include "Floor.h"
#include "cocos2d.h"

class MyEvent
{
public:
	MyEvent(int id,std::string decription);
	MyEvent(Floor*,int id,std::string description,int x,int y);
	void setFloorInfo(Floor*,int x,int y);
	~MyEvent(); 
	int getID();
	bool passable(); 
	//virtual bool isEnemy();
	virtual bool canAtk();
	bool canGet();
	bool canInteract();
	bool specialEffect();
	std::string getDescription();
	virtual cocos2d::Sprite* getSprite(int px,int py);
	//bool hasAnimation();
	//virtual bool hasFrameAnimation();

protected:
	Floor* floor;
	int id;
	int x;
	int y;
	std::string description;


	/*
	std::string imageName1;
	std::string imageName2;
	std::string description;
	int interactive; //0 - no, 1 - mob(fight), 2 - npc(dialog), 3 - store(?)
	bool passable;
	*/
};

