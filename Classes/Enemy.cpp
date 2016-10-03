#include "Enemy.h"
USING_NS_CC;

Enemy::Enemy(int id,std::string desc,int secondImageID,int hp,int atk,int def):MyEvent(id,desc),secondImageID(secondImageID),hp(hp),atk(atk),def(def){}

//perhaps do a dynamic_cast?
/*
Enemy::Enemy(Floor *f,int id,int x,int y,int secondImageID,int hp,int atk,int def):
	MyEvent(f,id,x,y),secondImageID(secondImageID),hp(hp),atk(atk),def(def){

}
*/

bool Enemy::canAtk(){
	return true;
}

Sprite* Enemy::getSprite(int px,int py){
	std::stringstream ss2;
	ss2<<"tile ("<<id<<").png";
	auto sprite2=Sprite::create(ss2.str());
	sprite2->setPosition(px,py);
	sprite2->setAnchorPoint(Vec2(0,0));
	std::stringstream ss3;
	ss3<<"tile ("<<secondImageID<<").png";
	//add animation
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrame::create(ss3.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	animFrames.pushBack(SpriteFrame::create(ss2.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	Animation* animation = Animation::createWithSpriteFrames(animFrames,0.3f);
	Animate* animate = Animate::create(animation);
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	sprite2->runAction(RepeatForever::create(animate));
	return sprite2;
}


Enemy::~Enemy(){
}
