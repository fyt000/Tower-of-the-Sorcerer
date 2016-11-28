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
	auto leftSprite=Sprite::create("Left.png");
	leftSprite->setPosition(leftX,0);
	leftSprite->setAnchorPoint(Vec2(0,0));
	leftSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(leftSprite,0);

	float lineRadiusH=24;
	float lineRadiusV=30;

	startX=leftX+leftSprite->getBoundingBox().size.width;
	auto centerSprite=Sprite::create("CENTER.png");
	centerSprite->setPosition(startX,0);
	centerSprite->setAnchorPoint(Vec2(0,0));
	centerSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(centerSprite,1);

	//draw a border
	float borderTopY=height-lineRadiusV;
	float borderBottomY=borderTopY-centerSprite->getBoundingBox().size.height-lineRadiusV;
	float borderLeftX=startX+lineRadiusH;
	float borderRightX=startX+centerSprite->getBoundingBox().size.width;
	/*
	log("borderTop %d",borderTopY);
	auto color=Color4F(156/255.0,99/255.0,66/255.0,1);
	auto drawNode = DrawNode::create();
	drawNode->drawSegment(Vec2(borderLeftX,borderTopY),Vec2(borderRightX,borderTopY),lineRadius,color);
	drawNode->drawSegment(Vec2(borderLeftX,borderBottomY),Vec2(borderRightX,borderBottomY),lineRadius,color);
	drawNode->drawSegment(Vec2(borderLeftX,borderTopY),Vec2(borderLeftX,borderBottomY),lineRadius,color);
	drawNode->drawSegment(Vec2(borderRightX,borderTopY),Vec2(borderRightX,borderBottomY),lineRadius,color);
	this->addChild(drawNode,2);
	*/
	//right static image
	auto rightSprite=Sprite::create("Right.png");
	rightSprite->setPosition(borderRightX,0);
	rightSprite->setAnchorPoint(Vec2(0,0));
	rightSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(rightSprite,0);

	startX=startX+lineRadiusH;

	auto gInstance = GameData::getInstance();

	std::string font="fonts/arial.ttf";
	int fontSize=15;

	gInstance->logLable = Label::createWithTTF("",font,20,Size::ZERO,TextHAlignment::CENTER);
	gInstance->logLable->enableGlow(Color4B::BLACK);
	gInstance->logLable->enableShadow();
	gInstance->logLable->setPosition(visibleSize.width/2,visibleSize.height/2);
	//gInstance->logLable->setAnchorPoint
	this->addChild(gInstance->logLable,20);
	floorContent = Node::create();


	float statX=137.5;
	float statY=397.5;

	gInstance->charHp = Label::createWithTTF(ToString(gInstance->hero.getHp()),font,fontSize,Size::ZERO,TextHAlignment::RIGHT);
	gInstance->charHp->setPosition(statX,statY);
	gInstance->charHp->setAnchorPoint(Vec2(1,1));
	this->addChild(gInstance->charHp,2);

	gInstance->charAtk = Label::createWithTTF(ToString(gInstance->hero.getAtk()),font,fontSize,Size::ZERO,TextHAlignment::RIGHT);
	gInstance->charAtk->setPosition(statX,statY-30);
	gInstance->charAtk->setAnchorPoint(Vec2(1,1));
	this->addChild(gInstance->charAtk,2);

	gInstance->charDef = Label::createWithTTF(ToString(gInstance->hero.getDef()),font,fontSize,Size::ZERO,TextHAlignment::RIGHT);
	gInstance->charDef->setPosition(statX,statY-60);
	gInstance->charDef->setAnchorPoint(Vec2(1,1));
	this->addChild(gInstance->charDef,2);

	gInstance->charGold = Label::createWithTTF(ToString(gInstance->hero.getGold()),font,fontSize,Size::ZERO,TextHAlignment::RIGHT);
	gInstance->charGold->setPosition(statX,statY-90);
	gInstance->charGold->setAnchorPoint(Vec2(1,1));
	this->addChild(gInstance->charGold,2);


	//display the floor
	//load the floor info
	//should use cache

	
	startY=height-40-lineRadiusV;
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
			floorContent->addChild(sprite1,2);

			auto sprite2=gInstance->getSprite(i,j);
			if (sprite2!=nullptr){
				sprite2->setScale(Director::getInstance()->getContentScaleFactor());
				floorContent->addChild(sprite2,3);
			}
		}
	}

	floorContent->addChild(gInstance->hero.getSprite(),10);

	this->addChild(floorContent,3);

	gInstance->floorMouseListener = EventListenerTouchAllAtOnce::create();
	gInstance->floorMouseListener->onTouchesEnded = CC_CALLBACK_2(FloorScene::onTouchesEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(GameData::getInstance()->floorMouseListener,this);

	return true;
}

//one of it is not right.
//TODO do this in TransformCoordinate.
/*
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
}*/



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
		auto blockDest=TransformCoordinate::computeBlock(loc.x,loc.y);
		//auto path=GameData::getInstance()->pathFind(blockDest);
		GameData::getInstance()->moveHero(blockDest);
	}
}



