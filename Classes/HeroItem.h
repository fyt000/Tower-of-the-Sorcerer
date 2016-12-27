#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <functional>

//the items that gets displayed on the left bottom corner
//position of the item is based on id for now
class HeroItem{

	
public:

	HeroItem(int id,std::string s,int imageID,std::function<void()> f,int uses=-1);
	void attachTo(cocos2d::Node*);
	bool isObtained();
	//all of the effects avaliable 
	static std::function<void()> getEffectFunction(const std::string&);
	//static void showFloorEnemyStats();



private:
	cocos2d::ui::Button* itemButton;
	int uses;
	int id;
	int imageID;
	std::function<void()> f;
	std::string desc;
	bool obtained=false;
};