#pragma once
#include <utility>
#include "cocos2d.h"

class TransformCoordinate{
public:
	static std::pair<int,int> transform(int x,int y);
	static cocos2d::Vec2 getVec2Diff(int x,int y,int nx,int ny);
	static cocos2d::Vec2 TransformCoordinate::transformVec2(int x,int y);
	static int startX;
	static int startY;
	static int const size=40;
};