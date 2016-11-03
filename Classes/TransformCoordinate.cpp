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

std::pair<int,int> TransformCoordinate::computeBlock(float x,float y){
	for (int i=0;i<11;i++)
		for (int j=0;j<11;j++){
			int curX = startX+j*40;
			int curY = startY-i*40;
			if (x>(curX)&&x<=curX+40&&y>curY&&y<=(curY+40)){
				CCLOG("block %d %d",i,j);
				return std::pair<int,int>(i,j);
			}
		}
	return std::pair<int,int>(-1,-1); //return empty?
}