#pragma once

#include "cocos2d.h"
#include <queue>

class FloorScene: public cocos2d::Layer
{
	Node* floorContent;
	float startX;
	float startY;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	

	//drawDialogs
	CREATE_FUNC(FloorScene);

	//std::pair<int,int> computeBlock(float x,float y);
	void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches,cocos2d::Event *event);

	//SeemsGood C++11 SeemsGood
	void drawDialog(std::string & text,enum DIALOGTYPE dType,std::vector<std::string>options={});

private:
	cocos2d::DrawNode* dialogNode;
	bool dialogOpen=false;
	enum DIALOGTYPE dialogType;
	void closeDialog(int);
};