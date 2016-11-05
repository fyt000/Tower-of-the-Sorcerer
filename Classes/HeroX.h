#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>
#include "GlobalDefs.h"

USING_NS_CC;

class HeroX:
	public Fightable
{
public:

	HeroX(int id,std::string desc,int hp,int atk,int def,int gold);

	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	int getGold();
	void gainGold(int amt);
	bool spendGold(int amt);
	cocos2d::Sprite* getSprite();
	void move(enum DIR dir);
	Animate * getDirMoveAnimate(DIR dir,int steps);
	void move(PATH path,bool isLastMove=false);
	void move(std::pair<int,int>);
	//items?
	virtual HeroX* clone();
	~HeroX();

	Label* charHp;
	Label* charAtk;
	Label* charDef;
	Label* charGold;

private:
	int gold;
	int secondImageID;
	enum DIR heroDir;
	float animateRate=0.1f;
	void changeDirAnimate(Node * node,DIR newDir,int steps);
	void Destined(Node* node,int x,int y);
	void StopAll(Node * node,std::pair<int,int>);
	void StopAllFinal(Node* node);
};

