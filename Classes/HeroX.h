#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>
#include "GlobalDefs.h"
#include "FightableSnapshot.h"

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
	int fight(Fightable * target,std::function<void(Fightable&)> hpCallback1,std::function<void(Fightable&)> hpCallback2);
	void cleanUpTarget(Node * node,Fightable * target);
	void move(enum DIR dir);
	Animate * getDirMoveAnimate(DIR dir,int steps);
	void move(PATH path,bool isLastMove=false);
	void move(std::pair<int,int>);
	//items?
	virtual HeroX* clone();
	~HeroX();

private:
	int gold;
	int secondImageID;
	enum DIR heroDir;
	float animateRate=0.1f;
	void changeDirAnimate(Node * node,DIR newDir,int steps);
	void Destined(Node* node,int x,int y);
	void StopAll(Node * node,std::pair<int,int>);
	void StopAllFinal(Node* node);
	void triggeredCallback(Node* node,MyEvent * ev);
	void updateBetweenFight(Node* n,std::vector<FightableSnapshot> &snapshots,int hSSIdx,SpriteFrame* newFrame,bool isHero=false);
};

