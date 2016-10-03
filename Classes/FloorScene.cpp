#include "FloorScene.h"
#include "HelloWorldScene.h"
#include <sstream>
#include "GameData.h"

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

	//make a global variable to hold these
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
	int events[]={
		11,0,0,0,0,0,0,0,0,0,0,
		8,8,8,8,8,8,8,8,8,8,0,
		32,0,0,1,0,8,0,29,0,8,0,
		0,77,0,8,0,8,0,32,0,8,0,
		8,1,8,8,0,8,8,8,1,8,0,
		29,0,0,8,0,1,67,69,67,8,0,
		0,79,0,8,0,8,8,8,8,8,0,
		8,1,8,8,0,0,0,0,0,0,0,
		0,0,0,8,8,1,8,8,8,1,8,
		32,0,29,8,29,0,0,8,0,67,0,
		32,38,29,8,0,0,0,8,61,33,61
	};


	//left static image
	float leftX=0;
	auto sprite1=Sprite::create("Left.png");
	sprite1->setPosition(leftX,0);
	sprite1->setAnchorPoint(Vec2(0,0));
	sprite1->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(sprite1,0);

	float lineRadius=3;

	float startX=leftX+sprite1->getBoundingBox().size.width+lineRadius;

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

	

	//display the floor
	//load the floor info
	//should use cache
	float startY=height-40-lineRadius;
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			//this is animatable as well
			//add a class for this
			std::stringstream ss1;
			ss1<<"tile ("<<tiles[i+11*j]<<").png";
			auto sprite1=Sprite::create(ss1.str());
			sprite1->setPosition(startX+i*40,startY-j*40);
			sprite1->setAnchorPoint(Vec2(0,0));
			sprite1->setScale(Director::getInstance()->getContentScaleFactor());
			this->addChild(sprite1,0);

			if (events[i+11*j]){
				auto temp=GameData::getInstance()->getEventData(events[i+11*j]);
				auto sprite2=temp->getSprite(startX+i*40,startY-j*40);
				sprite2->setScale(Director::getInstance()->getContentScaleFactor());
				this->addChild(sprite2,1);
			}
		}
	}

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(FloorScene::onTouchesEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void FloorScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,cocos2d::Event * event)
{
	log("touched");
	if (touches.size()==0){
		return;
	}
	//ignore all touches except the last one
	for (auto touch : touches){
		auto loc = touch->getLocationInView();
	}
}



