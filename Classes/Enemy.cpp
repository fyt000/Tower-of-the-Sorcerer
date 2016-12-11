#include "Enemy.h"
#include "GlobalDefs.h"
#include "TransformCoordinate.h"
#include "GameData.h"

USING_NS_CC;

Enemy::Enemy(int imageIdx,std::string desc,int secondImageID,int hp,int atk,int def,int gold):
	Fightable(imageIdx,desc,hp,atk,def,gold),secondImageID(secondImageID){}


bool Enemy::canAtk(){
	return true;
}

bool Enemy::stepOnEvent()
{
	bool fightR = Fightable::stepOnEvent();
	if (fightR)
		GameData::getInstance()->log("Beat "+description+". Received "+ToString(gold.V())+" gold.",false);
	return fightR;
}

Sprite* Enemy::getSprite(){
	std::stringstream ss2;
	ss2<<"images/tile ("<<imageIdx<<").png";
	auto sprite2=Sprite::create(ss2.str());
	std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
	sprite2->setPosition(pxy.first,pxy.second);
	sprite2->setAnchorPoint(Vec2(0,0));
	std::stringstream ss3;
	ss3<<"images/tile ("<<secondImageID<<").png";
	//add animation
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrame::create(ss3.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	animFrames.pushBack(SpriteFrame::create(ss2.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	Animation* animation = Animation::createWithSpriteFrames(animFrames,0.3f);
	Animate* animate = Animate::create(animation);
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	sprite2->runAction(RepeatForever::create(animate));
	sprite=sprite2;
	return sprite2;
}



Enemy::~Enemy(){
}

Enemy * Enemy::clone()
{
	return new Enemy(*this);
}
