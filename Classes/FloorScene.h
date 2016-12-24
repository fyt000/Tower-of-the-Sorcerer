#pragma once

#include "cocos2d.h"
#include <queue>
#include "GlobalDefs.h"

class FloorScene: public cocos2d::Layer
{
	
	float startX;
	float startY;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	void loadFloor();

	//drawDialogs
	CREATE_FUNC(FloorScene);

	//std::pair<int,int> computeBlock(float x,float y);
	void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches,cocos2d::Event *event);

	//SeemsGood C++11 SeemsGood
	void drawDialog(const std::string & text,enum DIALOGTYPE dType,std::vector<std::string>options={});

	void drawEnemyPortrait(cocos2d::Sprite* s);

	void showFloorEnemyStats(std::vector<std::tuple<cocos2d::Sprite*,std::string,int,int,int,int>>& stats);

private:
	cocos2d::Node* floorContent=nullptr;
	cocos2d::DrawNode* dialogNode;
	bool dialogOpen=false;
	enum DIALOGTYPE dialogType;
	int eSpriteX=-1;
	int eSpriteY=-1;
	cocos2d::Sprite* enemyInfoSprite=nullptr;

	void closeDialog(int);
};