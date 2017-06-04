#include "FloorScene.h"
#include <sstream>
#include "GameData.h"
#include "HeroX.h"
#include <utility>
#include "TransformCoordinate.h"
#include "LabelBinder.h"
#include <vector>

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
	float height = visibleSize.height;
	Point origin = Director::getInstance()->getVisibleOrigin();
	log("height %lf", height);

	//left static image
	float leftX = 0;
	auto leftSprite = Sprite::create("images/Left.png");
	leftSprite->setPosition(leftX, 0);
	leftSprite->setAnchorPoint(Vec2(0, 0));
	leftSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(leftSprite, 0);

	float lineRadiusH = 24;
	float lineRadiusV = 30;

	startX = leftX + leftSprite->getBoundingBox().size.width;
	auto centerSprite = Sprite::create("images/CENTER.png");
	centerSprite->setPosition(startX, 0);
	centerSprite->setAnchorPoint(Vec2(0, 0));
	centerSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(centerSprite, 1);

	//draw a border
	//float borderTopY=height-lineRadiusV;
	//float borderBottomY=borderTopY-centerSprite->getBoundingBox().size.height-lineRadiusV;
	//float borderLeftX=startX+lineRadiusH;
	float borderRightX = startX + centerSprite->getBoundingBox().size.width;

	//right static image
	auto rightSprite = Sprite::create("images/Right.png");
	rightSprite->setPosition(borderRightX, 0);
	rightSprite->setAnchorPoint(Vec2(0, 0));
	rightSprite->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(rightSprite, 0);

	startX = startX + lineRadiusH;

	//this is likely the place where GameData gets instantiated
	auto gInstance = GameData::getInstance();

	gInstance->flScn = this;

	//std::string font="fonts/arial.ttf";
	int fontSize = 15;
	gInstance->logLabel = Label::createWithSystemFont("", "Arial", 20, Size::ZERO, TextHAlignment::CENTER);
	gInstance->logLabel->enableGlow(Color4B::BLACK);
	gInstance->logLabel->enableShadow(Color4B::BLACK); //shadow appears to be white on KDE (perhaps it has to do with my theme?)
	gInstance->logLabel->setPosition(visibleSize.width / 2, 0);
	gInstance->logLabel->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(gInstance->logLabel, 20);



	float statX = 137.5;
	float statY = 397.5;


	auto charHpLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	charHpLabel->setPosition(statX, statY);
	charHpLabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(charHpLabel, 2);
	gInstance->hero->hp.attach(charHpLabel);
	//gInstance->hero->charHpLabel = charHpLabel;

	auto charAtkLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	charAtkLabel->setPosition(statX, statY - 30);
	charAtkLabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(charAtkLabel, 2);
	gInstance->hero->atk.attach(charAtkLabel);
	//gInstance->hero->charAtkLabel = charAtkLabel;

	auto charDefLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	charDefLabel->setPosition(statX, statY - 60);
	charDefLabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(charDefLabel, 2);
	gInstance->hero->def.attach(charDefLabel);
	//gInstance->hero->charDefLabel = charDefLabel;

	auto charGoldLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	charGoldLabel->setPosition(statX, statY - 90);
	charGoldLabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(charGoldLabel, 2);
	gInstance->hero->gold.attach(charGoldLabel);
	//gInstance->hero->charGoldLabel = charGoldLabel;

	int enemyInfoX = 700;
	int enemyInfoY = 170;

	eSpriteX = enemyInfoX;
	eSpriteY = enemyInfoY;

	//enemyInfoX-=25;
	enemyInfoY -= 25;

	enemyInfoX = 720;

	auto eDescLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::CENTER);
	eDescLabel->setPosition(enemyInfoX, enemyInfoY);
	eDescLabel->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(eDescLabel, 2);
	gInstance->eDescLabel = eDescLabel;

	enemyInfoX = 775;
	enemyInfoY -= 25;

	auto eHpLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	eHpLabel->setPosition(enemyInfoX, enemyInfoY);
	eHpLabel->setAnchorPoint(Vec2(1, 0));
	this->addChild(eHpLabel, 2);
	gInstance->eHpLabel = eHpLabel;

	enemyInfoY -= 25;

	auto eAtkLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	eAtkLabel->setPosition(enemyInfoX, enemyInfoY);
	eAtkLabel->setAnchorPoint(Vec2(1, 0));
	this->addChild(eAtkLabel, 2);
	gInstance->eAtkLabel = eAtkLabel;

	enemyInfoY -= 25;

	auto eDefLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	eDefLabel->setPosition(enemyInfoX, enemyInfoY);
	eDefLabel->setAnchorPoint(Vec2(1, 0));
	this->addChild(eDefLabel, 2);
	gInstance->eDefLabel = eDefLabel;


	for (int i = 0; i < KeyType::LAST; i++)
	{
		std::stringstream ss1;
		ss1 << "images/key_" << i << ".png";
		auto keySprite = Sprite::create(ss1.str());
		keySprite->setPosition(Vec2(664, 287 - 24 * i));
		keySprite->setAnchorPoint(Vec2(0, 0));
		keySprite->setScale(Director::getInstance()->getContentScaleFactor());
		this->addChild(keySprite, 2);
		auto keyLabel = Label::createWithSystemFont("", "Arial", 18, Size::ZERO, TextHAlignment::RIGHT);
		keyLabel->setPosition(Vec2(664 + 60, 296 - 24 * i));
		keyLabel->setAnchorPoint(Vec2(0, 0));
		this->addChild(keyLabel, 2);
		gInstance->hero->keys[i]->attach(keyLabel);
	}


	//29 430, 130 430
	auto floorTxtLabel = Label::createWithSystemFont(GStr("floor"), "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	floorTxtLabel->setPosition(Vec2(29, 430));
	floorTxtLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(floorTxtLabel, 2);

	auto floorNumLabel = Label::createWithSystemFont("", "Arial", fontSize, Size::ZERO, TextHAlignment::RIGHT);
	floorNumLabel->setPosition(Vec2(130, 430));
	floorNumLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(floorNumLabel, 2);
	gInstance->floor->attach(floorNumLabel);


	startY = height - 40 - lineRadiusV;
	CCLOG("start x %f y %f", startX, startY);

	TransformCoordinate::startX = startX;
	TransformCoordinate::startY = startY;

	TransformCoordinate::itemX = 20;
	TransformCoordinate::itemY = 255;

	loadFloor();


	gInstance->floorMouseListener = EventListenerTouchAllAtOnce::create();
	gInstance->floorMouseListener->onTouchesEnded = CC_CALLBACK_2(FloorScene::onTouchesEnded, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(FloorScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(FloorScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(GameData::getInstance()->floorMouseListener, this);

	return true;
}

void FloorScene::loadFloor()
{
	auto gInstance = GameData::getInstance();
	if (floorContent != nullptr) {
		//all children should be removed by now, except hero
		//floorContent->removeAllChildrenWithCleanup(true);
		floorContent->removeFromParentAndCleanup(true);
	}
	//display the floor
	//load the floor info

	floorContent = Node::create();
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			//this is animatable as well
			//add a class for this
			std::stringstream ss1;
			ss1 << "images/tile (6).png";
			auto sprite1 = Sprite::create(ss1.str());
			std::pair<int, int> pxy = TransformCoordinate::transform(i, j);
			sprite1->setPosition(pxy.first, pxy.second);
			sprite1->setAnchorPoint(Vec2(0, 0));
			sprite1->setScale(Director::getInstance()->getContentScaleFactor());
			floorContent->addChild(sprite1, 2);

			auto sprite2 = gInstance->getSprite(i, j);
			if (sprite2 != nullptr) {
				sprite2->setScale(Director::getInstance()->getContentScaleFactor());
				floorContent->addChild(sprite2, 3);
			}
		}
	}

	gInstance->eDescLabel->setString("");
	gInstance->eHpLabel->setString("");
	gInstance->eAtkLabel->setString("");
	gInstance->eDefLabel->setString("");

	enemyInfoSprite = nullptr; //?

	floorContent->addChild(gInstance->hero->getSprite(), 10);
	this->schedule(schedule_selector(FloorScene::stuckBreaker), 0);
	this->addChild(floorContent, 3);
}

//the ultimate solution #1
void FloorScene::stuckBreaker(float dt) {
	//CCLOG("scheduled actions %d", GameData::getInstance()->hero->getSprite()->numberOfRunningActions());
	auto hero = GameData::getInstance()->hero;
	if (hero->getSprite()->numberOfRunningActions() == 0 && !hero->moving()) {
		Director::getInstance()->getEventDispatcher()->setEnabled(true);
		GameData::getInstance()->replayHeroAction();
	}
}

void FloorScene::attachFloorSprite(cocos2d::Sprite* s) {
	floorContent->addChild(s, 3);
}


void FloorScene::drawDialog(const std::string& text, enum DIALOGTYPE dType, std::vector<std::string> options)
{
	if (dialogOpen)
		return;

	dialogType = dType;
	dialogOpen = true;
	dialogNode = DrawNode::create();
	Vec2 rectangle[4];

	int startX = 160;
	int vsize = 490;
	int startY = 450;
	int hsize = 300;
	rectangle[0] = Vec2(startX, startY);
	rectangle[1] = Vec2(startX + vsize, startY);
	rectangle[2] = Vec2(startX + vsize, startY - hsize);
	rectangle[3] = Vec2(startX, startY - hsize);
	Color4F transGray(Color3B::GRAY, 0.5);
	dialogNode->drawPolygon(rectangle, 4, transGray, 1, transGray);
	auto textLabel = Label::createWithSystemFont(text, "Arial", 18);
	textLabel->setPosition(Vec2(startX + 10, startY - 10));
	textLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
	textLabel->setDimensions(vsize - 20, 0);
	textLabel->setAnchorPoint(Vec2(0, 1));
	textLabel->enableGlow(Color4B::GRAY);
	textLabel->enableShadow(Color4B::BLACK, cocos2d::Size(1, -1), 1);
	dialogNode->addChild(textLabel, 2);

	absorbClick++;

	switch (dType) {
	case DIALOGTYPE::YN: {

		int fontSize = 18;
		MenuItemFont::setFontSize(fontSize);
		MenuItemFont::setFontName("Arial");
		auto yesItem = MenuItemFont::create(GStr("yes"), [this](Ref *pSender)->void {
			closeDialog(0);
		});
		auto noItem = MenuItemFont::create(GStr("no"), [this](Ref *pSender)->void {
			closeDialog(1);
		});

		float menuX = startX + vsize - 100;
		float menuY = startY - hsize + 30;

		auto *menu = Menu::create(yesItem, noItem, NULL);
		menu->alignItemsHorizontallyWithPadding(50);
		menu->setAnchorPoint(Vec2(0, 0));
		menu->setPosition(Vec2(menuX, menuY));
		//menu->setSwallowTouches(true);
		dialogNode->addChild(menu, 3);
		break;
	}
	case DIALOGTYPE::LIST: {

		int fontSize = 25;
		MenuItemFont::setFontSize(fontSize);
		MenuItemFont::setFontName("Arial");

		auto *menu = Menu::create();

		int idx = 0;
		for (auto option : options) {
			auto item = MenuItemFont::create(option, [this, idx](Ref *pSender)->void {
				closeDialog(idx);
			});
			menu->addChild(item);
			idx++;

		}
		//float menuX=550; //auto middle
		float menuY = 300;
		menu->setPositionY(menuY);
		menu->setAnchorPoint(Vec2(0, 0));
		menu->alignItemsVerticallyWithPadding(10);
		dialogNode->addChild(menu, 3);
		break;
	}
	case DIALOGTYPE::MATRIX: {
		int fontSize = 18;
		int itemsPerRow = 5; //hopefully no long strings, so it will fit
		int startY = 350;
		int itemsLeft = options.size();
		for (int i = 0;; i++) {
			if (!itemsLeft)
				break;
			int curItems = itemsPerRow;
			if (itemsLeft < itemsPerRow) {
				curItems = itemsLeft;
			}
			auto* subMenu = Menu::create();
			for (int j = 0; j < curItems; j++) {
				auto item = MenuItemFont::create(options[i*itemsPerRow + j], [i, itemsPerRow, j, this](Ref *pSender)->void {
					closeDialog(i*itemsPerRow + j);
				});
				subMenu->addChild(item);
			}
			itemsLeft -= curItems;
			subMenu->setPositionY(startY);
			startY -= (fontSize*1.5);
			subMenu->setAnchorPoint(Vec2(0, 0));
			subMenu->alignItemsHorizontallyWithPadding(10);
			dialogNode->addChild(subMenu);
		}

		/*
		MenuItemFont::setFontSize(fontSize);
		MenuItemFont::setFontName("Arial");

		auto *menu = Menu::create();
		menu->setContentSize(Size(vsize,hsize)); //uselss

		std::vector<Value> itemsInCol;

		int idx=0;
		for (auto option: options){
			auto item = MenuItemFont::create(option,[this,idx](Ref *pSender)->void{
				closeDialog(idx);
			});
			menu->addChild(item);
			idx++;
			if (idx%itemsPerRow==0){
				itemsInCol.emplace_back(itemsPerRow);
			}
		}
		if (idx%itemsPerRow!=0){
			itemsInCol.emplace_back(idx%itemsPerRow);
		}

		float menuY=300;
		menu->setPositionY(menuY);
		menu->setAnchorPoint(Vec2(0,0));

		//this uses Size winSize = Director::getInstance()->getWinSize();
		//why do they think this is a good idea? - logged an issue, they are working on it
		menu->alignItemsInColumnsWithArray(itemsInCol);
		dialogNode->addChild(menu,3);
		*/
		break;
	}
	case DIALOGTYPE::NONE:break;
	}
	this->addChild(dialogNode, 100);
}

void FloorScene::drawEnemyPortrait(Sprite * s)
{
	if (enemyInfoSprite != nullptr) {
		enemyInfoSprite->removeFromParent();
	}
	s->setPositionX(eSpriteX);
	s->setPositionY(eSpriteY);
	enemyInfoSprite = s;
	if (floorContent != nullptr)
		floorContent->addChild(s);
}

//fake it with dialog, since whatever, or refactor dialog into something more general
void FloorScene::showFloorEnemyStats(std::vector<std::tuple<Sprite*, std::string, int, int, int, int>>& stats)
{

	if (dialogOpen)
		return;

	dialogOpen = true;
	dialogType = DIALOGTYPE::NONE;

	//using the same code as dialog for now, will change this
	dialogNode = DrawNode::create();
	Vec2 rectangle[4];

	int startx = TransformCoordinate::startX;
	int vsize = 11 * 40;
	int startY = TransformCoordinate::startY + 40;
	int hsize = 11 * 40;

	rectangle[0] = Vec2(startx, startY);
	rectangle[1] = Vec2(startx + vsize, startY);
	rectangle[2] = Vec2(startx + vsize, startY - hsize);
	rectangle[3] = Vec2(startx, startY - hsize);
	Color4F transGray(Color3B::GRAY, 0.75);
	dialogNode->drawPolygon(rectangle, 4, transGray, 1, transGray);

	int spriteX = startx + 15;
	int spriteY = startY - 10;

	int descX = spriteX + 40 + 10;
	int descY = spriteY;

	int expectedDmgX = descX + 150;
	int expectedDmgY = descY;

	int statX = descX;
	int statY = spriteY - 20;

	int fontSize = 18;

	for (auto& item : stats) {
		Sprite* sprite = std::get<0>(item);
		std::string& desc = std::get<1>(item);
		int hp = std::get<2>(item);
		int atk = std::get<3>(item);
		int def = std::get<4>(item);
		int dmg = std::get<5>(item);

		sprite->setPositionX(spriteX);
		sprite->setPositionY(spriteY);
		sprite->setAnchorPoint(Vec2(0, 1));
		dialogNode->addChild(sprite);

		auto descLabel = Label::createWithSystemFont(desc, "Arial", fontSize, Size::ZERO, TextHAlignment::LEFT);
		descLabel->setPosition(Vec2(descX, descY));
		descLabel->setAnchorPoint(Vec2(0, 1));
		dialogNode->addChild(descLabel, 2);

		auto dmgLabel = Label::createWithSystemFont(stdsprintf(GStr("expected_damage"), dmg), "Arial", fontSize, Size::ZERO, TextHAlignment::LEFT);
		dmgLabel->setPosition(Vec2(expectedDmgX, expectedDmgY));
		dmgLabel->setAnchorPoint(Vec2(0, 1));
		dialogNode->addChild(dmgLabel, 2);

		auto statLabel = Label::createWithSystemFont(stdsprintf(GStr("enemy_stat"), hp, atk, def), "Arial", fontSize, Size::ZERO, TextHAlignment::LEFT);
		statLabel->setPosition(Vec2(statX, statY));
		statLabel->setAnchorPoint(Vec2(0, 1));
		dialogNode->addChild(statLabel, 2);

		spriteY -= 55;
		descY -= 55;
		expectedDmgY -= 55;
		statY -= 55;
	}
	this->addChild(dialogNode, 100);
}



void FloorScene::closeDialog(int c)
{
	absorbClick = 1;
	dialogOpen = false;
	if (dialogNode != nullptr) {
		dialogNode->removeFromParent();
		dialogNode = nullptr;
	}
	GameData::getInstance()->dialogCompleted(c);
}

void FloorScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (dialogOpen) {
		//or close dialog?
		return;
	}

	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		currentMovement = DIR::UP; movementActive = true; break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		currentMovement = DIR::DOWN; movementActive = true; break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		currentMovement = DIR::LEFT; movementActive = true; break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		currentMovement = DIR::RIGHT; movementActive = true; break;
	}
	
	continousMovement();

}

void FloorScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	movementActive = false;
}

void FloorScene::continousMovement() {
	if (movementActive) {
		//I hoped I used future or something
		GameData::getInstance()->moveHero(currentMovement); 
	}
}


void FloorScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * event)
{
	//clicking on menuitem will actually trigger onTouchesEnded as well
	//so we use dialogOpen to ignore the first click after closeDialog
	if (dialogOpen) {
		if (dialogType == DIALOGTYPE::NONE) {
			closeDialog(0);
			absorbClick = 0;
			return;
		}
	}

	if (absorbClick) {
		absorbClick--;
		if (dialogNode != nullptr)
			absorbClick++;
		return;
	}


	if (touches.size() == 0) {
		return;
	}

	//ignore all touches except the last one
	for (auto touch : touches) {
		auto loc = touch->getLocation();
		CCLOG("clicked %f %f", loc.x, loc.y);
		//need to first check if the loc is within the UI region.
		auto blockDest = TransformCoordinate::computeBlock(loc.x, loc.y);

		GameData::getInstance()->moveHero(blockDest);
	}
	//GameData::getInstance()->freePendingFreeList();
}



