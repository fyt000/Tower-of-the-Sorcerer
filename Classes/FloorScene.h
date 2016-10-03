#pragma once

#include "cocos2d.h"

class FloorScene: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	
	CREATE_FUNC(FloorScene);
	void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches,cocos2d::Event *event);
};