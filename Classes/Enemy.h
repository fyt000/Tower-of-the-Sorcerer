#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"

class Enemy:
	public Fightable
{
public:
	Enemy(int id,std::string desc,int secondImageID,int hp,int atk,int def);
	
	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	cocos2d::Sprite* getSprite();
	virtual ~Enemy();
	Enemy* clone();

private:
	int secondImageID;
};

