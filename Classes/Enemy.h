#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"

class Enemy :
	public Fightable
{
public:
	Enemy(int imageIdx, const std::string& decription, int secondImageID, int hp, int atk, int def, int gold);

	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	virtual bool triggerEvent();
	virtual bool stepOnEvent();
	virtual ~Enemy();

};

