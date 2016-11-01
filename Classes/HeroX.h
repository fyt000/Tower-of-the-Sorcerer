#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>

USING_NS_CC;
//there might be a name conflict somewhere I don't know about
class HeroX:
	public Fightable
{
public:
	HeroX(int id,std::string desc,int hp,int atk,int def);

	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	cocos2d::Sprite* getSprite();
	void move(enum DIR dir);
	void move(std::pair<int,int> dest);
	Animate * getDirMoveAnimate(DIR dir,int steps);
	void move(std::vector<std::pair<int,int>> path);
	//items?
	virtual HeroX* clone();
	~HeroX();


private:
	int secondImageID;
	enum DIR heroDir;
	float animateRate=0.1f;
	void changeDirAnimate(Node * node,DIR newDir,int steps);
	void Destined(Node* node,int x,int y);
	void StopAll(Node * node);
};

