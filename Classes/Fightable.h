#pragma once
#include "MyEvent.h"
#include "cocos2d.h"
#include <string>
#include <map>
#include "LabelBinder.h"

class HeroX;

//uhm. things are not as straight forward
//to cheat - make things easier to implement
//use special map to check if there are special effects etc...
class Fightable:
	public MyEvent
{
public:
	Fightable(int imageIdx,const std::string& desc,int imageIdx2,int hp,int atk,int def,int gold);
	//virtual cocos2d::Sprite* getSprite(int px,int py);
	virtual ~Fightable();
	virtual Fightable* clone()=0;
	virtual int fight(Fightable * target,std::function<void(Fightable&)> hpCallback1,std::function<void(Fightable&)> hpCallback2);
	const int getHp();
	const int getAtk();
	const int getDef();
	virtual bool triggerEvent();
	virtual bool stepOnEvent();
	//special attack effects on this later...
	virtual int hitBy(Fightable*);
	virtual int hit(Fightable*);
	void decHp(int amt);
	void setLabelNofity(bool n);
	bool attackable(HeroX*);

	LabelBinder<int> hp;
	LabelBinder<int> atk;
	LabelBinder<int> def;
	LabelBinder<int> gold;

protected:
	std::map<std::string,int> effects;
	

private:
	int secondImageID;
};
