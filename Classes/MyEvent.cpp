#include "MyEvent.h"
#include "TransformCoordinate.h"
#include <sstream>

USING_NS_CC;
//id has to match the image id
MyEvent::MyEvent(int id,std::string desc):id(id),description(desc),sprite(NULL){
	x=-1;
	y=-1;
}

MyEvent * MyEvent::clone()
{
	return new MyEvent(*this);
}

MyEvent::~MyEvent(){}

void MyEvent::setXY(int x,int y)
{
	this->x=x;
	this->y=y;
}

int MyEvent::getID(){
	return id;
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
	ss1<<"tile ("<<id<<").png";
	auto sprite1=Sprite::create(ss1.str());
	sprite1->setPosition(pxy.first,pxy.second);
	sprite1->setAnchorPoint(Vec2(0,0));
	sprite1->setScale(Director::getInstance()->getContentScaleFactor()); 
	sprite=sprite1;
	return sprite1;
}

void MyEvent::triggerEvent()
{
}

int MyEvent::getX()
{
	return x;
}

int MyEvent::getY()
{
	return y;
}



/*
bool MyEvent::hasAnimation(){
	return false;
}*/