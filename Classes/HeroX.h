#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include "Fightable.h"
#include <utility>
#include "GlobalDefs.h"
#include "FightableSnapshot.h"
#include "Key.h"
#include "LabelBinder.h"
#include <atomic>


class HeroX :
	public Fightable
{

	typedef std::vector< std::pair< PATH, enum DIR> > DirectedPath;

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
	std::pair<int,int> getDirXY(enum DIR dir);
	void moveOnestep(PATH& path);
	//animation to move dir steps, stop=true for extra swagger
	cocos2d::Animate * getDirMoveAnimate(DIR dir, int steps, bool stop = false);
	//move the given path, isLastMove means to trigger the event on the last move
	void move(PATH& path, bool isLastMove = false);
	void move(std::pair<int, int>);

	//initialized in Hero constructor
	LabelBinder<int>* keys[KeyType::LAST]; //3 types of keys - each key will be the same type
	void changeFacingDir(enum DIR);
	//based to the given xy
	void changeFacingDir(std::pair<int, int>);
	//set absolute position and facing dir of hero
	void setAbsPos(int, int, enum DIR);
	//virtual HeroX* clone();
	//callback to stop everything
	void StopAllFinal(cocos2d::Node* node, bool reset = true, bool cont = true);
	void setMoving(bool moving);
	bool moving();
	~HeroX();

private:
	enum DIR heroDir;
	float animateRate = 0.1f;
	std::atomic_bool isMoving = false;
	DirectedPath getDirectedPath(PATH& path);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> createMoveActions(DirectedPath& directedPath);
	void changeDirAnimate(cocos2d::Node * node, DIR newDir, int steps, bool stop = false);
	void Destined(cocos2d::Node* node, int x, int y);
	void StopAll(cocos2d::Node * node, std::pair<int, int>);
	void triggeredCallback(cocos2d::Node* node, MyEvent * ev);
	void updateBetweenFight(cocos2d::Node * n, Fightable * f, std::vector<FightableSnapshot>& snapshots, int hSSIdx, std::string & frameName, bool isHero);
	cocos2d::SpriteFrame* stopSprite(DIR dir);
	
};

