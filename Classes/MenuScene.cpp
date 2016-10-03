#include "MenuScene.h"
#include "FloorScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("open0.png");
	sprite->setAnchorPoint(Vec2(0,0));
	sprite->setPosition(0,0);
	sprite->setScale(Director::getInstance()->getContentScaleFactor()); //no auto scaling?

	this->addChild(sprite,0);


	int fontSize=25;

	MenuItemFont::setFontSize(fontSize);
	MenuItemFont::setFontName("OpenSans-Regular");

	auto menu_item_1 = MenuItemFont::create("START",[](Ref *pSender)->void{
		auto scene = FloorScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	auto menu_item_2 = MenuItemFont::create("HIGHSCORE",[](Ref *pSender)->void{
		log("highscore");
	});
	auto menu_item_3 = MenuItemFont::create("SETTING",[](Ref *pSender)->void{
		log("settings");
	});

	float menuX=visibleSize.width*0.2;
	float menuY=visibleSize.height*0.75;

	auto *menu = Menu::create(menu_item_1,menu_item_2,menu_item_3,NULL);
	menu->alignItemsVerticallyWithPadding(fontSize);
	menu->setPosition(menuX,menuY);
	//menu->setColor(Color3B(0.0f,0.0f,0.0f));
	this->addChild(menu);



	return true;
}

