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
	sprite->removeFromParent();
}

void MyEvent::setXY(int x,int y)
{
	this->x=x;
	this->y=y;
}

int MyEvent::getID(){
	return imageIdx;
}
bool MyEvent::passable(){
	return false;
}
bool MyEvent::canAtk(){
	return false;
}
bool MyEvent::canGet(){
	return false;
}
bool MyEvent::canInteract(){
	return false;
}
bool MyEvent::specialEffect(){
	return false;
}
std::string MyEvent::getDescription()
{
	return description;
}
Sprite* MyEvent::getSprite(){
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
	//GameData::getInstance()->log("You used The destructible Ball! Enemies on all sides died!");
	selfDestruct();
	return true;
}

bool MyEvent::stepOnEvent(){
	//GameData::getInstance()->log("step on event");
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

void MyEvent::selfDestruct()
{
	GameData::getInstance()->killEvent(std::pair<int,int>(getX(),getY()));
}



/*
bool MyEvent::hasAnimation(){
	return false;
}*/