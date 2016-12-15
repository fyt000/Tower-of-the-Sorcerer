#include "FloorScene.h"
#include <sstream>
#include "GameData.h"
#include "HeroX.h"
#include <utility>
#include "TransformCoordinate.h"
#include "LabelBinder.h"

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
	auto leftSprite=Sprite::create("images/Left.png");
	leftSprite->setPosition(leftX,0);
	leftSprite->setAnchorPoint(Vec2(0,0));
	leftSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(leftSprite,0);

	float lineRadiusH=24;
	float lineRadiusV=30;

	startX=leftX+leftSprite->getBoundingBox().size.width;
	auto centerSprite=Sprite::create("images/CENTER.png");
	centerSprite->setPosition(startX,0);
	centerSprite->setAnchorPoint(Vec2(0,0));
	centerSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(centerSprite,1);

	//draw a border
	float borderTopY=height-lineRadiusV;
	float borderBottomY=borderTopY-centerSprite->getBoundingBox().size.height-lineRadiusV;
	float borderLeftX=startX+lineRadiusH;
	float borderRightX=startX+centerSprite->getBoundingBox().size.width;

	//right static image
	auto rightSprite=Sprite::create("images/Right.png");
	rightSprite->setPosition(borderRightX,0);
	rightSprite->setAnchorPoint(Vec2(0,0));
	rightSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(rightSprite,0);

	startX=startX+lineRadiusH;

	auto gInstance = GameData::getInstance();

	gInstance->flScn=this;

	//std::string font="fonts/arial.ttf";
	int fontSize=15;
	gInstance->logLabel = Label::createWithSystemFont("","Arial",20,Size::ZERO,TextHAlignment::CENTER);
	gInstance->logLabel->enableGlow(Color4B::BLACK);
	gInstance->logLabel->enableShadow();
	gInstance->logLabel->setPosition(visibleSize.width/2,0);
	gInstance->logLabel->setAnchorPoint(Vec2(0.5,0));
	this->addChild(gInstance->logLabel,20);
	


	float statX=137.5;
	float statY=397.5;

	
	auto charHpLabel = Label::createWithSystemFont("","Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	charHpLabel->setPosition(statX,statY);
	charHpLabel->setAnchorPoint(Vec2(1,1));
	this->addChild(charHpLabel,2);
	gInstance->hero.hp.attach(charHpLabel);
	//gInstance->hero.charHpLabel = charHpLabel;

	auto charAtkLabel = Label::createWithSystemFont("","Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	charAtkLabel->setPosition(statX,statY-30);
	charAtkLabel->setAnchorPoint(Vec2(1,1));
	this->addChild(charAtkLabel,2);
	gInstance->hero.atk.attach(charAtkLabel);
	//gInstance->hero.charAtkLabel = charAtkLabel;

	auto charDefLabel = Label::createWithSystemFont("","Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	charDefLabel->setPosition(statX,statY-60);
	charDefLabel->setAnchorPoint(Vec2(1,1));
	this->addChild(charDefLabel,2);
	gInstance->hero.def.attach(charDefLabel);
	//gInstance->hero.charDefLabel = charDefLabel;

	auto charGoldLabel = Label::createWithSystemFont("","Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	charGoldLabel->setPosition(statX,statY-90);
	charGoldLabel->setAnchorPoint(Vec2(1,1));
	this->addChild(charGoldLabel,2);
	gInstance->hero.gold.attach(charGoldLabel);
	//gInstance->hero.charGoldLabel = charGoldLabel;

	for (int i=0;i<KeyType::LAST;i++)
	{
		std::stringstream ss1;
		ss1<<"images/key_"<<i<<".png";
		auto keySprite=Sprite::create(ss1.str());
		keySprite->setPosition(Vec2(664,287-24*i));
		keySprite->setAnchorPoint(Vec2(0,0));
		keySprite->setScale(Director::getInstance()->getContentScaleFactor());
		this->addChild(keySprite,2);
		auto keyLabel = Label::createWithSystemFont("","Arial",18,Size::ZERO,TextHAlignment::RIGHT);
		keyLabel->setPosition(Vec2(664+60,296-24*i));
		keyLabel->setAnchorPoint(Vec2(0,0));
		this->addChild(keyLabel,2);
		gInstance->hero.keys[i]->attach(keyLabel);
		/*
		auto charGoldLabel = Label::createWithSystemFont(ToString(gInstance->hero.),font,fontSize,Size::ZERO,TextHAlignment::RIGHT);
		charGoldLabel->setPosition(statX,statY-90);
		charGoldLabel->setAnchorPoint(Vec2(1,1));
		this->addChild(charGoldLabel,2);
		*/
	}


	//29 430, 130 430
	auto floorTxtLabel = Label::createWithSystemFont(GStr("floor"),"Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	floorTxtLabel->setPosition(Vec2(29,430));
	floorTxtLabel->setAnchorPoint(Vec2(0,0.5));
	this->addChild(floorTxtLabel,2);

	auto floorNumLabel = Label::createWithSystemFont("","Arial",fontSize,Size::ZERO,TextHAlignment::RIGHT);
	floorNumLabel->setPosition(Vec2(130,430));
	floorNumLabel->setAnchorPoint(Vec2(0,0.5));
	this->addChild(floorNumLabel,2);
	gInstance->floor.attach(floorNumLabel);


	//display the floor
	//load the floor info
	//should use cache

	floorContent = Node::create();
	startY=height-40-lineRadiusV;
	CCLOG("start x %f y %f",startX,startY);

	TransformCoordinate::startX=startX;
	TransformCoordinate::startY=startY;
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){

			//this is animatable as well
			//add a class for this
			std::stringstream ss1;
			ss1<<"images/tile ("<<tiles[j+11*i]<<").png";
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
	/*
	std::string longText="I need to write a sentence. I need to write a sentence. I need to write a sentence. I need to write a sentence. I need to write a sentence. I need to write a sentence.";
	drawDialog(longText,DIALOGTYPE::SHOP,{"hello","darkness","myold","friend"});
	*/
	return true;
}

void FloorScene::drawDialog(std::string& text,enum DIALOGTYPE dType,std::vector<std::string> options)
{
	dialogType=dType;
	dialogOpen=true;
	dialogNode = DrawNode::create();
	Vec2 rectangle[4];
	int startx=150;
	int vsize=500;
	rectangle[0] = Vec2(150,450);
	rectangle[1] = Vec2(startx+vsize,450);
	rectangle[2] = Vec2(startx+vsize,100);
	rectangle[3] = Vec2(150,100);
	Color4F transGray(Color3B::GRAY,0.75);
	dialogNode->drawPolygon(rectangle,4,transGray,1,Color4F::WHITE);
	auto textLabel = Label::createWithSystemFont(text,"Arial",18);
	textLabel->setPosition(Vec2(startx+10,440));
	textLabel->setAlignment(TextHAlignment::LEFT,TextVAlignment::TOP);
	textLabel->setDimensions(vsize-20,0);
	textLabel->setAnchorPoint(Vec2(0,1));
	dialogNode->addChild(textLabel,2);

	switch (dType){
		case DIALOGTYPE::YN:{
			int fontSize = 18;
			MenuItemFont::setFontSize(fontSize);
			MenuItemFont::setFontName("Arial");

			auto yesItem = MenuItemFont::create(GStr("yes"),[this](Ref *pSender)->void{
				closeDialog(0);
			});
			auto noItem = MenuItemFont::create(GStr("no"),[this](Ref *pSender)->void{
				closeDialog(1);
			});

			float menuX=550;
			float menuY=130;

			auto *menu = Menu::create(yesItem,noItem, NULL);
			menu->alignItemsHorizontallyWithPadding(50);
			menu->setAnchorPoint(Vec2(0,0));
			menu->setPosition(Vec2(menuX,menuY));
			dialogNode->addChild(menu,3);
		}
		case DIALOGTYPE::SHOP:{
			int fontSize = 25;
			MenuItemFont::setFontSize(fontSize);
			MenuItemFont::setFontName("Arial");

			auto *menu = Menu::create();

			int idx=0;
			for (auto option: options){
				auto item = MenuItemFont::create(option,[this,idx](Ref *pSender)->void{
					closeDialog(idx);
				});
				menu->addChild(item);
				idx++;

			}
			//float menuX=550; //auto middle
			float menuY=300;
			menu->setPositionY(menuY);
			menu->setAnchorPoint(Vec2(0,0));
			menu->alignItemsVerticallyWithPadding(10);
			dialogNode->addChild(menu,3);
		}
	}
	this->addChild(dialogNode,100);
}

void FloorScene::closeDialog(int c)
{
	if (dialogNode!=nullptr){
		dialogNode->removeFromParent();
		dialogNode=nullptr;
	}
	GameData::getInstance()->dialogCompleted(c);
}


void FloorScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,cocos2d::Event * event)
{
	//clicking on menuitem will actually trigger onTouchesEnded as well
	//so we use dialogOpen to ignore the first click after closeDialog
	if (dialogOpen){
		if (dialogType==DIALOGTYPE::NONE){
			closeDialog(0);
		}
		if (dialogNode==nullptr){
			dialogOpen=false;
		}
		return;
	}

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



