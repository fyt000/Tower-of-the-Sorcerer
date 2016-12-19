#include "MyEvent.h"
#include "TransformCoordinate.h"
#include <sstream>
#include "GameData.h"

USING_NS_CC;
//id has to match the image id
MyEvent::MyEvent(int imageIdx,std::string desc):imageIdx(imageIdx),description(desc){
	x=-1;
	y=-1;
}

MyEvent::MyEvent(int imageIdx,std::string decription,int imageIdx2):imageIdx(imageIdx),description(decription),imageIdx2(imageIdx2)
{
}

MyEvent * MyEvent::clone()
{
	return new MyEvent(*this);
}

MyEvent::~MyEvent(){
	if (sprite!=nullptr){
		sprite->removeFromParentAndCleanup(true);
	}
}

void MyEvent::setXY(int x,int y)
{
	this->x=x;
	this->y=y;
}

bool MyEvent::canAtk(){
	return false;
}

std::string MyEvent::getDescription()
{
	return Configureader::GetDescription(description);
}
Sprite* MyEvent::getSprite(bool createNew){
	if (sprite!=nullptr&&!createNew){
		return sprite;
	}
	
	//TODO refactor
	if (imageIdx2==-1){
		std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
		std::stringstream ss1;
		ss1<<"images/tile ("<<imageIdx<<").png";
		auto sprite1=Sprite::create(ss1.str());
		sprite1->setPosition(pxy.first,pxy.second);
		sprite1->setAnchorPoint(Vec2(0,0));
		sprite1->setScale(Director::getInstance()->getContentScaleFactor());
		if (sprite==nullptr)
			sprite=sprite1;
		return sprite1;
	}
	else{
		std::stringstream ss2;
		ss2<<"images/tile ("<<imageIdx<<").png";
		auto sprite2=Sprite::create(ss2.str());
		std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
		sprite2->setPosition(pxy.first,pxy.second);
		sprite2->setAnchorPoint(Vec2(0,0));
		std::stringstream ss3;
		ss3<<"images/tile ("<<imageIdx2<<").png";
		//add animation
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create(ss3.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
		animFrames.pushBack(SpriteFrame::create(ss2.str(),Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
		Animation* animation = Animation::createWithSpriteFrames(animFrames,0.3f);
		Animate* animate = Animate::create(animation);
		sprite2->setScale(Director::getInstance()->getContentScaleFactor());
		sprite2->runAction(RepeatForever::create(animate));
		if (sprite==nullptr)
			sprite=sprite2;
		return sprite2;
	}
}

bool MyEvent::triggerEvent()
{
	performActions();
	return false;
}

bool MyEvent::stepOnEvent(){
	//GameData::getInstance()->log("step on event")
	selfDestruct();
	return false;
}

int MyEvent::getX()
{
	return x;
}

int MyEvent::getY()
{
	return y;
}

void MyEvent::attachAction(MyAction *action)
{
	actions.push_back(action);
}

int MyEvent::performActions()
{
	for (int i=0;i<actions.size();i++)
		actions[i]->perform(this);
	//if performActions marked to delete this
	//sigh... async problems again
	//introduce some global callback stack and callback chaining mechanism maybe

	return 1;
}

void MyEvent::selfDestruct()
{
	if (GameData::getInstance()->getEvent(getX(),getY())==this) //could have been replaced already
		GameData::getInstance()->killEvent(std::pair<int,int>(getX(),getY()));
	else
	{
		delete this;
	}
}
