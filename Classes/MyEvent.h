#pragma once
#include <string>
#include "cocos2d.h"

class MyEvent
{
public:
	MyEvent(int id,std::string decription);
	virtual MyEvent* clone();
	virtual ~MyEvent(); 
	void setXY(int x,int y);
	int getID();
	bool passable(); 
	//virtual bool isEnemy();
	virtual bool canAtk();
	bool canGet();
	bool canInteract();
	bool specialEffect();
	std::string getDescription();
	virtual cocos2d::Sprite* getSprite();
	virtual bool triggerEvent();
	virtual bool stepOnEvent();
	int getX();
	int getY();
	//virtual int calcDamage();

	//this method works like this:
	//f is a function ptr that expects a MyEvent and returns void
	//hit the enemy, pass the enemy back to f, f will then update the graphics
	//f will probably also fetch hero data .. I don't know
	//virtual int engage(void (*f) (MyEvent*));
	//bool hasAnimation();
	//virtual bool hasFrameAnimation();

protected:
	int id;
	int x;
	int y;
	std::string description;
	cocos2d::Sprite* sprite;

	/*
	std::string imageName1;
	std::string imageName2;
	std::string description;
	int interactive; //0 - no, 1 - mob(fight), 2 - npc(dialog), 3 - store(?)
	bool passable;
	*/
};

