#include "MyEvent.h"
#include <sstream>

USING_NS_CC;
//id has to match the image id
MyEvent::MyEvent(int id,std::string desc):id(id),description(desc){}
MyEvent::MyEvent(Floor *f,int id,std::string desc,int x,int y):floor(f),id(id),description(desc),x(x),y(y){}

void MyEvent::setFloorInfo(Floor *f,int x,int y){
	floor=f;
	x=x;
	y=y;
}

MyEvent::~MyEvent(){}

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
Sprite* MyEvent::getSprite(int px,int py){
	std::stringstream ss1;
	ss1<<"tile ("<<id<<").png";
	auto sprite1=Sprite::create(ss1.str());
	sprite1->setPosition(px,py);
	sprite1->setAnchorPoint(Vec2(0,0));
	sprite1->setScale(Director::getInstance()->getContentScaleFactor()); 
	return sprite1;
}


/*
bool MyEvent::hasAnimation(){
	return false;
}*/