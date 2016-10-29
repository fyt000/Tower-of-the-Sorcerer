#pragma once

#include "cocos2d.h"

class FloorScene: public cocos2d::Layer
{
	Node* floorContent;
	float startX;
	float startY;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	
	CREATE_FUNC(FloorScene);

	std::pair<int,int> computeBlock(float x,float y);
	void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches,cocos2d::Event *event);
};