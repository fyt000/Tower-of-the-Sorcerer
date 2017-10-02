#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>
#include "GlobalDefs.h"
#include "FightableSnapshot.h"
#include "Key.h"
#include "LabelBinder.h"


class HeroX :
	public Fightable
{

	typedef std::vector< std::pair< twsutil::PATH, twsutil::DIR> > DirectedPath;

public:

	HeroX(int imageIdx, const std::string& desc, int hp, int atk, int def, int gold);

	//return true if sufficient gold
	bool spendGold(int amt);
	cocos2d::Sprite* getSprite();
	//call this for fight
	int fightX(Fightable * target, std::function<void(Fightable&)> hpCallback1, std::function<void(Fightable&)> hpCallback2);
	//remove fighting target and other clean up before enabling user input
	void cleanUpTarget(cocos2d::Node * node, Fightable * target);
	//not exactly used, may be needed for keyboard
	std::pair<int,int> getDirXY(twsutil::DIR dir);
	void moveOnestep(std::pair<int, int>);
	//animation to move dir steps, stop=true for extra swagger
	cocos2d::Animate * getDirMoveAnimate(twsutil::DIR dir, int steps, bool stop = false);
	//move the given path, isLastMove means to trigger the event on the last move

	//initialized in Hero constructor
	LabelBinder<int>* keys[KeyType::LAST]; //3 types of keys - each key will be the same type
	//set absolute position and facing dir of hero
	void setAbsPos(int, int, twsutil::DIR);
	//virtual HeroX* clone();
	//callback to stop everything
	void StopAllFinal(cocos2d::Node* node, bool reset = true, bool cont = true);
	void setMoving(bool moving);
	bool moving();
	int getX();
	int getY();
	
	~HeroX();

private:
	twsutil::DIR heroDir;
	bool isEvenStep = true; 
	float animateRate = 0.1f;
	bool isMoving = false;
	void updateBetweenFight(cocos2d::Node * n, Fightable * f, std::vector<FightableSnapshot>& snapshots, int hSSIdx, std::string & frameName, bool isHero);
	cocos2d::SpriteFrame* stopSprite(twsutil::DIR dir);
	// handle interleaving
	int prevX;
	int prevY;
	bool prevComplete = true;
};

