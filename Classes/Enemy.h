#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"

class Enemy:
	public Fightable
{
public:
	Enemy(int imageIdx,std::string desc,int secondImageID,int hp,int atk,int def,int gold);
	
	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	bool stepOnEvent();
	virtual ~Enemy();
	Enemy* clone();

};

