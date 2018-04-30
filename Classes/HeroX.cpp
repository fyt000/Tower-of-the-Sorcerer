#include "HeroX.h"
#include "TransformCoordinate.h"
#include "GameData.h"
#include "FightableSnapshot.h"
#include "LabelBinder.h"

USING_NS_CC;
using namespace twsutil;

HeroX::HeroX(int imageIdx, const std::string& desc, int hp, int atk, int def, int gold) :Fightable(imageIdx, desc, -1, hp, atk, def, gold) {
	//hard coding these for now
	x = 10; y = 1;
	heroDir = DIR::UP;
}

int HeroX::getGold() 
{
	return gold.V();
}

bool HeroX::spendGold(int amt) {
	if (gold.V() >= amt) {
		gold.subVal(amt);
		return true;
	}
	return false;
}


Sprite* HeroX::getSprite() {

	if (sprite != NULL) {
		return sprite;
	}
	std::stringstream ss2;
	ss2 << "images/tile (" << imageIdx << ").png";
	auto sprite2 = Sprite::create(ss2.str());
	std::pair<int, int> pxy = TransformCoordinate::transform(x, y);
	sprite2->setPosition(pxy.first, pxy.second);
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	sprite2->setAnchorPoint(Vec2(0, 0));
	sprite = sprite2;
	return sprite2;
}

int HeroX::fightX(Fightable * target, std::function<void(Fightable&)> hpCallback1, std::function<void(Fightable&)> hpCallback2) {
	//hpCallBack should really just be null... I don't care
	//this may change
	CCLOG("disabled input on fightX");
	GameData::getInstance().block();
	target->setLabelNofity(false);
	this->setLabelNofity(false);
	std::vector<FightableSnapshot> heroSnapshots;
	std::vector<FightableSnapshot> enemySnapshots;
	//this allows calculation done in one method... without jumping around
	int ret = Fightable::fight(target,
		[&enemySnapshots](Fightable &f) {
		FightableSnapshot ss(f.getHp(), f.getAtk(), f.getDef());
		enemySnapshots.push_back(ss);
	},
		[&heroSnapshots](Fightable &f) { //capture heroSnapshots 
		FightableSnapshot ss(f.getHp(), f.getAtk(), f.getDef());
		heroSnapshots.push_back(ss);
	}
	);

	//simulate everything by callbacks...
	//because this is way too advanced for me

	std::string stepFrame1;
	std::string stepFrame2;
	switch (heroDir) {
	case DIR::DOWN:stepFrame1 = "images/tile (189).png"; stepFrame2 = "images/tile (191).png"; break;
	case DIR::LEFT:stepFrame1 = "images/tile (197).png"; stepFrame2 = "images/tile (199).png"; break;
	case DIR::RIGHT:stepFrame1 = "images/tile (205).png"; stepFrame2 = "images/tile (207).png"; break;
	case DIR::UP:stepFrame1 = "images/tile (213).png"; stepFrame2 = "images/tile (215).png"; break;
	default:stepFrame1 = "images/tile (213).png"; stepFrame2 = "images/tile (215).png";
	}
	//log("has frames %d",heroSnapshots.size());
	Vector<FiniteTimeAction*> actions;
	int hSSIdx = 0;
	int eSSIdx = 0;
	target->setLabelNofity(true);
	this->setLabelNofity(true);
	for (std::size_t i = 0; i < heroSnapshots.size() + enemySnapshots.size(); i++) {
		if (i % 2 == 0) {
			//enemy action		
			auto enemyCallback = CallFuncN::create(CC_CALLBACK_1(HeroX::updateBetweenFight, this, target, enemySnapshots, eSSIdx, stepFrame2, false));
			eSSIdx++;
			actions.pushBack(enemyCallback);
			actions.pushBack(DelayTime::create(0.3f));
		}
		else {

			auto heroCallback = CallFuncN::create(CC_CALLBACK_1(HeroX::updateBetweenFight, this, this, heroSnapshots, hSSIdx, stepFrame1, true));
			hSSIdx++;
			actions.pushBack(heroCallback);
			actions.pushBack(DelayTime::create(0.3f));
		}
	}
	auto cb2 = CallFuncN::create([this](Node* n) {
		CCLOG("going to run stopAllFinal");
		this->StopAllFinal(n,true,false);
	});
	auto cb1 = CallFuncN::create([this,target](Node* n) {
		CCLOG("going to cleanup target");
		cleanUpTarget(n, target);
	});
	actions.pushBack(cb1);
	actions.pushBack(cb2);
	CCLOG("running fighting sequence");
	sprite->runAction(Sequence::create(actions));
	return ret;
}

void HeroX::cleanUpTarget(Node* node, Fightable * target) {
	GameData::getInstance().killEvent(std::pair<int, int>(target->getX(), target->getY()));
	GameData::getInstance().triggerGlobalEvents();
}

void HeroX::updateBetweenFight(Node* n, Fightable* f, std::vector<FightableSnapshot> &snapshots, int hSSIdx, std::string &frameName, bool isHero) {
	auto& gInst = GameData::getInstance();
	f->hp.setVal(snapshots[hSSIdx].hp);
	f->atk.setVal(snapshots[hSSIdx].atk);
	f->def.setVal(snapshots[hSSIdx].def);
	CCLOG("updating between fight %s",f->getDescription().c_str());
	//f==this means its hero->..
	if (isHero&&hp.V() <= 0) {
		CCLOG("stopped all action on defeat");
		sprite->stopAllActions();
		gInst.gameover();
		return;
	}
	auto newFrame = SpriteFrame::create(frameName, Rect(0, 0, 40 / Director::getInstance()->getContentScaleFactor(), 40 / Director::getInstance()->getContentScaleFactor()));
	sprite->setSpriteFrame(newFrame);
	CCLOG("updateBetweenFight done");
}

DIR nextNodeDir(std::pair<int, int> cur, std::pair<int, int> next) {
	if (next.first - cur.first > 0)
		return(DIR::DOWN);
	else if (next.first - cur.first < 0)
		return(DIR::UP);
	else if (next.second - cur.second > 0)
		return(DIR::RIGHT);
	else if (next.second - cur.second < 0)
		return(DIR::LEFT);
	return DIR::UP;
}


Animate* HeroX::getDirMoveAnimate(DIR dir, int steps, bool stop) {
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(steps + 2);

	std::string stepFrame1;
	std::string stepFrame2;
	//hard coding the pngs
	switch (dir) {
	case DIR::DOWN:stepFrame1 = "images/tile (185).png"; stepFrame2 = "images/tile (187).png"; break;
	case DIR::LEFT:stepFrame1 = "images/tile (193).png"; stepFrame2 = "images/tile (195).png"; break;
	case DIR::RIGHT:stepFrame1 = "images/tile (201).png"; stepFrame2 = "images/tile (203).png"; break;
	case DIR::UP:stepFrame1 = "images/tile (209).png"; stepFrame2 = "images/tile (211).png"; break;
	default:stepFrame1 = "images/tile (209).png"; stepFrame2 = "images/tile (211).png";
	}

	for (int i = 0; i < steps + 1; i++) {
		if ((i % 2 == 0) == isEvenStep)
			animFrames.pushBack(SpriteFrame::create(stepFrame1, Rect(0, 0, 40 / Director::getInstance()->getContentScaleFactor(), 40 / Director::getInstance()->getContentScaleFactor())));
		else
			animFrames.pushBack(SpriteFrame::create(stepFrame2, Rect(0, 0, 40 / Director::getInstance()->getContentScaleFactor(), 40 / Director::getInstance()->getContentScaleFactor())));
	}
	if (stop) {
		animFrames.pushBack(stopSprite(dir));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, animateRate);
	Animate* animate = Animate::create(animation);
	return animate;
}


//this is used for arrow(keyboard) movement if I happen to implement it
//but again, this does not make any assumption on its surroundings
//just move
std::pair<int, int> HeroX::getDirXY(DIR direction) {

	int newX = x; int newY = y;
	switch (direction) {
	case (DIR::UP):
		newX--; break;
	case(DIR::DOWN):
		newX++; break;
	case(DIR::LEFT):
		newY--; break;
	case(DIR::RIGHT):
		newY++; break;
	}

	return { newX,newY };
}

void HeroX::moveOnestep(std::pair<int,int> dest) {
	DIR nextDir = nextNodeDir({getX(),getY()}, dest);

	// Swaggering, could play it right away I think
	auto swagger = getDirMoveAnimate(nextDir,1,false);
	// this->getSprite()->runAction(swagger);
	isEvenStep=!isEvenStep;
	// before we do the animation for move, update the location
	// any other movement will not happen before the nextStep call
	this->setXY(dest.first, dest.second);
	heroDir = nextDir;

	CCLOG("will run MoveTo nextStep sequence");
	// Gotta chain the next call only after the movement is done
	auto seq = Sequence::create(
		MoveTo::create(animateRate,
			TransformCoordinate::transformVec2(dest.first, dest.second)),
		CallFunc::create([]() {
			GameData::getInstance().nextStep();
		}), 
		nullptr
	);
	auto moveAndAnimate = Spawn::createWithTwoActions(swagger, seq);
	this->getSprite()->runAction(moveAndAnimate);
}

//theres a few lines of copied code... get ride of it maybe
void HeroX::StopAllFinal(Node * node, bool reset, bool cont)
{
	CCLOG("final movement cleanup");
	if (reset) {
		GameData::getInstance().releaseBlock();
		GameData::getInstance().finalMovementCleanup(cont);
	}
	sprite->setSpriteFrame(stopSprite(heroDir));
}

void HeroX::setMoving(bool moving)
{
	isMoving = moving;
	if (!isMoving) {
		getSprite()->setSpriteFrame(stopSprite(heroDir));
	}
}

bool HeroX::moving()
{
	return isMoving;
}

SpriteFrame* HeroX::stopSprite(DIR dir) {
	std::string stopStr;
	switch (dir) {
	case DIR::DOWN:stopStr = "images/tile (189).png"; break;
	case DIR::LEFT:stopStr = "images/tile (197).png"; break;
	case DIR::RIGHT:stopStr = "images/tile (205).png"; break;
	case DIR::UP:stopStr = "images/tile (213).png"; break;
	default:stopStr = "images/tile (213).png";
	}
	return SpriteFrame::create(stopStr, Rect(0, 0, 40 / Director::getInstance()->getContentScaleFactor(), 40 / Director::getInstance()->getContentScaleFactor()));
}

int HeroX::getX()
{
	if (prevComplete)
		return MyEvent::getX();
	return prevX;
}

int HeroX::getY()
{
	if (prevComplete)
		return MyEvent::getY();
	return prevY;
}

HeroX::~HeroX() {
}


void HeroX::setAbsPos(int absx, int absy, DIR dir)
{
	setXY(absx, absy);
	std::pair<int, int> pxy = TransformCoordinate::transform(absx, absy);
	sprite->setPosition(pxy.first, pxy.second);
	heroDir = dir;
	getSprite()->setSpriteFrame(stopSprite(dir));
}
