#include "MyEvent.h"
#include "TransformCoordinate.h"
#include <sstream>
#include "GameData.h"

USING_NS_CC;
//id has to match the image id
MyEvent::MyEvent(int imageIdx,std::string desc):imageIdx(imageIdx),description(desc),sprite(NULL){
	x=-1;
	y=-1;
}

MyEvent * MyEvent::clone()
{
	return new MyEvent(*this);
}

MyEvent::~MyEvent(){
	if (sprite!=nullptr){
		sprite->removeFromParent();
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
Sprite* MyEvent::getSprite(){
	if (sprite!=nullptr){
		return sprite;
	}
	std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
	std::stringstream ss1;
	ss1<<"images/tile ("<<imageIdx<<").png";
	auto sprite1=Sprite::create(ss1.str());
	sprite1->setPosition(pxy.first,pxy.second);
	sprite1->setAnchorPoint(Vec2(0,0));
	sprite1->setScale(Director::getInstance()->getContentScaleFactor()); 
	sprite=sprite1;
	return sprite1;
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



/*
bool MyEvent::hasAnimation(){
	return false;
}*/