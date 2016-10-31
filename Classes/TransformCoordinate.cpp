#include "TransformCoordinate.h"
#include "cocos2d.h"

int TransformCoordinate::startX;
int TransformCoordinate::startY;

std::pair<int,int> TransformCoordinate::transform(int x, int y){
	return std::pair<int,int>(startX+y*size,startY-x*size);
}

cocos2d::Vec2 TransformCoordinate::transformVec2(int x,int y){
	return cocos2d::Vec2(startX+y*size,startY-x*size);
}

cocos2d::Vec2 TransformCoordinate::getVec2Diff(int x,int y,int nx,int ny)
{
	auto oldCoord=transform(x,y);
	auto newCoord=transform(nx,ny);
	return cocos2d::Vec2(newCoord.first-oldCoord.first,newCoord.second-oldCoord.second);
}