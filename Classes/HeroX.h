#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>
#include "GlobalDefs.h"
#include "FightableSnapshot.h"
#include "Key.h"
#include "LabelBinder.h"


class HeroX:
	public Fightable
{
public:

	HeroX(int id,std::string desc,int hp,int atk,int def,int gold);

	//Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def);
	bool canAtk();
	bool spendGold(int amt);
	cocos2d::Sprite* getSprite();
	int fight(Fightable * target,std::function<void(Fightable&)> hpCallback1,std::function<void(Fightable&)> hpCallback2);
	void cleanUpTarget(cocos2d::Node * node,Fightable * target);

	void move(enum DIR dir);
	cocos2d::Animate * getDirMoveAnimate(DIR dir,int steps,bool stop=false);
	void move(PATH path,bool isLastMove=false);
	void move(std::pair<int,int>);

	//initialized in Hero constructor
	LabelBinder<int>* keys[KeyType::LAST]; //3 types of keys - each key will be the same type

	void changeFacingDir(std::pair<int,int>);
	virtual HeroX* clone();
	~HeroX();

private:
	int secondImageID;
	enum DIR heroDir;
	float animateRate=0.1f;
	void changeDirAnimate(cocos2d::Node * node,DIR newDir,int steps,bool stop=false);
	void Destined(cocos2d::Node* node,int x,int y);
	void StopAll(cocos2d::Node * node,std::pair<int,int>);
	void StopAllFinal(cocos2d::Node* node);
	void triggeredCallback(cocos2d::Node* node,MyEvent * ev);
	void updateBetweenFight(cocos2d::Node * n,Fightable * f,std::vector<FightableSnapshot>& snapshots,int hSSIdx,std::string & frameName,bool isHero);
	cocos2d::SpriteFrame* stopSprite(DIR dir);

};

