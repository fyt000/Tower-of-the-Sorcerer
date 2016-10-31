#include "FloorScene.h"
#include "HelloWorldScene.h"
#include <sstream>
#include "GameData.h"
#include "HeroX.h"
#include <utility>
#include "TransformCoordinate.h"

USING_NS_CC;

Scene* FloorScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FloorScene::create();
	scene->addChild(layer);
	
	return scene;
}

bool FloorScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	float height=visibleSize.height;
	height=500;
	Point origin = Director::getInstance()->getVisibleOrigin();
	log("height %d",height);

	//for now assume everything is the same
	int tiles[]={6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,6,6,6,6,6,6,6,6
	};

	//left static image
	float leftX=0;
	auto sprite1=Sprite::create("Left.png");
	sprite1->setPosition(leftX,0);
	sprite1->setAnchorPoint(Vec2(0,0));
	sprite1->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(sprite1,0);

	float lineRadius=3;

	startX=leftX+sprite1->getBoundingBox().size.width+lineRadius;

	//draw a border
	float borderTopY=height-lineRadius;
	log("borderTop %d",borderTopY);
	float borderBottomY=borderTopY-11*40-lineRadius;
	auto color=Color4F(156/255.0,99/255.0,66/255.0,1);
	auto drawNode = DrawNode::create();
	drawNode->drawSegment(Vec2(startX,borderTopY),Vec2(startX+11*40,borderTopY),lineRadius,color);
	drawNode->drawSegment(Vec2(startX,borderBottomY),Vec2(startX+11*40,borderBottomY),lineRadius,color);
	drawNode->drawSegment(Vec2(startX,borderTopY),Vec2(startX,borderBottomY),lineRadius,color);
	drawNode->drawSegment(Vec2(startX+11*40,borderTopY),Vec2(startX+11*40,borderBottomY),lineRadius,color);
	this->addChild(drawNode,2);

	//right static image
	auto sprite2=Sprite::create("Right.png");
	sprite2->setPosition(startX+11*40+lineRadius,0);
	sprite2->setAnchorPoint(Vec2(0,0));
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(sprite2,0);

	
	floorContent = Node::create();
	//display the floor
	//load the floor info
	//should use cache

	
	startY=height-40-lineRadius;
	CCLOG("start x %f y %f",startX,startY);

	TransformCoordinate::startX=startX;
	TransformCoordinate::startY=startY;
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){

			//this is animatable as well
			//add a class for this
			std::stringstream ss1;
			ss1<<"tile ("<<tiles[j+11*i]<<").png";
			auto sprite1=Sprite::create(ss1.str());
			std::pair<int,int> pxy=TransformCoordinate::transform(i,j);
			sprite1->setPosition(pxy.first,pxy.second);
			sprite1->setAnchorPoint(Vec2(0,0));
			sprite1->setScale(Director::getInstance()->getContentScaleFactor());
			floorContent->addChild(sprite1,0);

			auto sprite2=GameData::getInstance()->getSprite(i,j);
			if (sprite2!=nullptr){
				sprite2->setScale(Director::getInstance()->getContentScaleFactor());
				floorContent->addChild(sprite2,1);
			}
		}
	}

	floorContent->addChild(GameData::getInstance()->hero.getSprite());

	this->addChild(floorContent);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(FloorScene::onTouchesEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

//one of it is not right.
//TODO do this in TransformCoordinate.
std::pair<int,int> FloorScene::computeBlock(float x,float y){
	for (int i=0;i<11;i++)
		for (int j=0;j<11;j++){
			int curX = startX+j*40;
			int curY = startY-i*40;
			if (x>(curX)&&x<=curX+40&&y>curY&&y<=(curY+40)){
				CCLOG("block %d %d",i,j);
				return std::pair<int,int>(i,j);
			}
		}
	return std::pair<int,int>(-1,-1); //return empty?
}

void FloorScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,cocos2d::Event * event)
{

	if (touches.size()==0){
		return;
	}
	//this->removeChild(floorContent);
	//ignore all touches except the last one
	for (auto touch : touches){
		auto loc = touch->getLocation();
		CCLOG("clicked %f %f",loc.x,loc.y);
		//need to first check if the loc is within the UI region.
		auto blockDest=computeBlock(loc.x,loc.y);
		auto path=GameData::getInstance()->pathFind(blockDest);
		/*
		for (auto pathNode: path){
			CCLOG("path %d %d",pathNode.first,pathNode.second);
			GameData::getInstance()->moveHero(pathNode);
		}*/
		GameData::getInstance()->moveHero(path);
	}
}



