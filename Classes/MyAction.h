#pragma once
#include <string>
#include <functional>
#include "GlobalDefs.h"
//action carries out an action that is attached to a event
//aside from very few things, events do not have a state, you `Transform' into another event

class MyEvent;

class MyAction {
public:
	MyAction();
	MyAction(MyAction*);
	virtual int perform(MyEvent*);
	virtual ~MyAction();
protected:
	//action chaining
	MyAction* next;
};


class Obtain :public MyAction {
public:
	Obtain(MyAction*, int item);
	int perform(MyEvent*);
private:
	int item;
};

//NONE type dialog
class Talk : public MyAction {
public:
	Talk(MyAction*, const std::string& tag);
	virtual int perform(MyEvent*);
	virtual ~Talk();
protected:
	void showDialog(std::function<void(int)>);
	std::string tag;
	enum DIALOGTYPE type;
};

//Y N choice dialog
class TalkYN : public Talk {
public:
	TalkYN(MyAction*, const std::string& tag);
	virtual int perform(MyEvent*);
};

//TODO TalkY class, so I can place transform etc into the callback


//transform the attached event into another event
//this is no state in an event
class TransformSelf : public MyAction {
public:
	TransformSelf(MyAction*, int id);
	virtual int perform(MyEvent*);
private:
	int id;
};

//TODO add animation type?
class Transform : public MyAction {
public:
	Transform(MyAction*, int floor, int x, int y, int targetID);
	virtual int perform(MyEvent*);
private:
	int floor;
	int x;
	int y;
	int targetID;
};

//show action log on screen
class LogText : public MyAction {
public:
	LogText(MyAction*, const std::string& tag);
	virtual int perform(MyEvent*);
private:
	std::string tag;
};

//gain stats...used by weapon consumables
//TODO PercentStat for percentage increase
class FlatStat : public MyAction {
public:
	FlatStat(MyAction*, const std::string& desc, int hp, int atk, int def, int gold);
	virtual int perform(MyEvent*);
private:
	std::string desc;
	int hp;
	int atk;
	int def;
	int gold;
};

//TransformSelf to 0 without freependinglist
class DestructSelf : public MyAction {
public:
	DestructSelf(MyAction*);
	virtual int perform(MyEvent*);
};
