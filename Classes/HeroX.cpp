#include "HeroX.h"
#include "TransformCoordinate.h"
#include "GameData.h"

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int,int>> PATH;

HeroX::HeroX(int id,std::string desc,int hp,int atk,int def):Fightable(id,desc,hp,atk,def){
	//hard coding these for now
	x=0;y=1;
	heroDir=DIR::UP;
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

enum DIR nextNodeDir(std::pair<int,int> cur,std::pair<int,int> next){
	if (next.first-cur.first>0)
		return(DIR::DOWN);
	else if (next.first-cur.first<0)
		return(DIR::UP);
	else if (next.second-cur.second>0)
		return(DIR::RIGHT);
	else if (next.second-cur.second<0)
		return(DIR::LEFT);
}



Animate* HeroX::getDirMoveAnimate(enum DIR dir,int steps){
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(steps);
	//all direction uses the same png for now... will fix!

	std::string stepFrame1;
	std::string stepFrame2;
	switch (dir){
		case DIR::DOWN:stepFrame1="tile (185).png";stepFrame2="tile (187).png";break;
		case DIR::LEFT:stepFrame1="tile (193).png";stepFrame2="tile (195).png";break;
		case DIR::RIGHT:stepFrame1="tile (201).png";stepFrame2="tile (203).png";break;
		case DIR::UP:stepFrame1="tile (209).png";stepFrame2="tile (211).png";break;
		default:stepFrame1="tile (209).png";stepFrame2="tile (211).png";
	}

	for (int i=0;i<steps+1;i++){
		if (i%2==0)
			animFrames.pushBack(SpriteFrame::create(stepFrame1,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
		else
			animFrames.pushBack(SpriteFrame::create(stepFrame2,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames,animateRate);
	Animate* animate = Animate::create(animation);
	animate->setTag(0); //all animations are 0
	return animate;
}

//THIS WORKS!!
void HeroX::move(PATH path){
	sprite->stopAllActions();
	if (path.size()==0)
		return;

	//break down the path into directions...
	//because each direction has a different animation
	std::vector< std::pair< PATH, enum DIR> > directedPaths;
	enum DIR curDir=heroDir;
	std::pair<int,int> curCoord(x,y); //do I need a lock on x,y or something
	PATH singleDirPath;
	for (int i=0;i<path.size();i++){
		enum DIR nextDir = nextNodeDir(curCoord,path[i]);
		if (nextDir!=curDir){ //change of direction
			if (singleDirPath.size()!=0)
				directedPaths.push_back( std::pair<PATH,enum DIR>(singleDirPath,curDir));
			curDir=nextDir;
			singleDirPath.clear();
		}
		curCoord=path[i];
		singleDirPath.push_back(curCoord);
	}
	if (singleDirPath.size()!=0)
		directedPaths.push_back(std::pair<PATH,enum DIR>(singleDirPath,curDir));



	//I could have combined this with the above code
	//but just in case I decide to do something different
	Vector<FiniteTimeAction*> actions;

	//now directedPaths stores all the stuff... 
	for (auto singPath:directedPaths){
		auto changeDirCallBack = CallFuncN::create(CC_CALLBACK_1(HeroX::changeDirAnimate,this,singPath.second,singPath.first.size()));
		actions.pushBack(changeDirCallBack);
		for (auto pathNode:singPath.first){
			auto destCoord=TransformCoordinate::transformVec2(pathNode.first,pathNode.second);
			auto callback = CallFuncN::create(CC_CALLBACK_1(HeroX::Destined,this,pathNode.first,pathNode.second));
			actions.pushBack(MoveTo::create(animateRate,destCoord));
			actions.pushBack(callback);
		}
	}
	actions.pushBack(DelayTime::create(animateRate));
	auto stopCallBack = CallFuncN::create(CC_CALLBACK_1(HeroX::StopAll,this));
	actions.pushBack(stopCallBack);
	auto seq = Sequence::create(actions);
	sprite->runAction(seq);
}

void HeroX::changeDirAnimate(Node* node,enum DIR newDir,int steps){
	heroDir=newDir;
	auto animate=getDirMoveAnimate(newDir,steps);
	sprite->stopActionByTag(0); //stop cur animation if any
	sprite->runAction(animate);
}

void HeroX::Destined(Node* node,int x,int y){
	this->x=x;this->y=y;
}

void HeroX::StopAll(Node* node){
	sprite->stopAllActions();
	std::string stopStr;
	switch (heroDir){
	case DIR::DOWN:stopStr="tile (189).png";break;
	case DIR::LEFT:stopStr="tile (197).png";break;
	case DIR::RIGHT:stopStr="tile (205).png";break;
	case DIR::UP:stopStr="tile (213).png";break;
	default:stopStr="tile (213).png";
	}
	sprite->setSpriteFrame(SpriteFrame::create(stopStr,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
}

HeroX::~HeroX(){
}

HeroX * HeroX::clone()
{
	return new HeroX(*this);
}
