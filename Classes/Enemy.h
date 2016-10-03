#pragma once
#include "MyEvent.h"
#include "cocos2d.h"

class Enemy:
	public MyEvent
{
public:
	Enemy(int id,std::string desc,int secondImageID,int hp,int atk,int def);
	
	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	cocos2d::Sprite* getSprite(int px,int py);
	~Enemy();

protected:
	int hp;
	int atk;
	int def;


private:
	int secondImageID;
};

