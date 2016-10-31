#include "HeroX.h"
#include "TransformCoordinate.h"
#include "GameData.h"



HeroX::HeroX(int id,std::string desc,int hp,int atk,int def):Fightable(id,desc,hp,atk,def){
	//hard coding these for now
	x=0;y=1;
}


bool HeroX::canAtk(){
	return true;
}

Sprite* HeroX::getSprite(){
	/*
	if (sprite!=NULL){
		sprite->removeFromParentAndCleanup(true);
	}*/
	std::stringstream ss2;
	ss2<<"tile ("<<id<<").png";
	auto sprite2=Sprite::create(ss2.str());
	std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
	sprite2->setPosition(pxy.first,pxy.second);
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	sprite2->setAnchorPoint(Vec2(0,0));
	sprite=sprite2;
	return sprite2;
}

//there are a lot of stuff that can happen with move
//for now, just do the animation
//and the logic for hitting the wall should be done else where maybe GameData
//TODO FIX THIS
void HeroX::move(enum DIR direction){
	MoveTo* moveTo;
	int oldX=x;int oldY=y;
	switch (direction){
	case (DIR::UP):
		x--;break;
	case(DIR::DOWN):
		x++;break;
	case(DIR::LEFT):
		y--;break;
	case(DIR::RIGHT):
		y++;break;
	}
	//could just use moveTo.... ok
	moveTo = MoveTo::create(0.5,TransformCoordinate::transformVec2(x,y));
	sprite->runAction(moveTo);

	
}

//TODO FIX THIS
void HeroX::move(std::pair<int,int> dest){
	/*
	if (dest.first-x>0)
		move(DIR::DOWN);
	else if (dest.first-x<0)
		move(DIR::UP);
	else if (dest.second-y>0)
		move(DIR::RIGHT);
	else if (dest.second-y<0)
		move(DIR::LEFT);
		*/
	x=dest.first;y=dest.second;
	auto destCoord=TransformCoordinate::transformVec2(x,y);
	CCLOG("dest coord %f %f",destCoord.x,destCoord.y);
	sprite->stopAllActions();
	//sprite->setPosition(destCoord.x,destCoord.y);
	auto moveTo = MoveTo::create(0.3,destCoord);
	sprite->runAction(moveTo);
}

//THIS WORKS!!
void HeroX::move(std::vector<std::pair<int,int>> path){
	sprite->stopAllActions();
	if (path.size()==0)
		return;
	Vector<FiniteTimeAction*> actions;
	for (auto pathNode:path){
		auto destCoord=TransformCoordinate::transformVec2(pathNode.first,pathNode.second);
		auto callback = CallFuncN::create(CC_CALLBACK_1(HeroX::Destined,this,pathNode.first,pathNode.second));
		actions.pushBack(MoveTo::create(0.1,destCoord));
		actions.pushBack(callback);
	}
	auto seq = Sequence::create(actions);
	sprite->runAction(seq);
}

void HeroX::Destined(Node* node,int x,int y){
	this->x=x;this->y=y;
}

HeroX::~HeroX(){
}

HeroX * HeroX::clone()
{
	return new HeroX(*this);
}
