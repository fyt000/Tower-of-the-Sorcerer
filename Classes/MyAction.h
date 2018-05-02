#pragma once
#include <string>
#include <functional>
#include <memory>
#include "GlobalDefs.h"
//action carries out an action that is attached to a event
//aside from very few things, events do not have a state, you `Transform' into another event

class MyEvent;

class MyAction {
public:
	MyAction();
	MyAction(std::unique_ptr<MyAction>);
	virtual int perform(std::shared_ptr<MyEvent>);
	virtual ~MyAction();
protected:
	//action chaining
	std::unique_ptr<MyAction> next;
};


class Obtain :public MyAction {
public:
	Obtain(std::unique_ptr<MyAction>, int item);
	virtual ~Obtain();
	int perform(std::shared_ptr<MyEvent>);
private:
	int item;
};

//NONE type dialog
class Talk : public MyAction {
public:
	Talk(std::unique_ptr<MyAction>, const std::string& tag);
	virtual int perform(std::shared_ptr<MyEvent>);
	virtual ~Talk();
protected:
	void showDialog(std::function<void(int)>);
	std::string tag;
	twsutil::DIALOGTYPE type;
};

//Y N choice dialog
class TalkYN : public Talk {
public:
	TalkYN(std::unique_ptr<MyAction>, const std::string& tag);
	virtual ~TalkYN();
	virtual int perform(std::shared_ptr<MyEvent>);
};

//TODO TalkY class, so I can place transform etc into the callback


//transform the attached event into another event
//this is no state in an event
class TransformSelf : public MyAction {
public:
	TransformSelf(std::unique_ptr<MyAction>, int id);
	~TransformSelf();
	virtual int perform(std::shared_ptr<MyEvent>);
private:
	int id;
};

//TODO add animation type?
class Transform : public MyAction {
public:
	Transform(std::unique_ptr<MyAction>, int floor, int x, int y, int targetID);
	~Transform();
	virtual int perform(std::shared_ptr<MyEvent>);
private:
	int floor;
	int x;
	int y;
	int targetID;
};

//show action log on screen
class LogText : public MyAction {
public:
	LogText(std::unique_ptr<MyAction>, const std::string& tag);
	~LogText();
	virtual int perform(std::shared_ptr<MyEvent>);
private:
	std::string tag;
};

// gain stats...used by weapon consumables
// TODO PercentStat for percentage increase
// gold doesn't work yet...
class FlatStat : public MyAction {
public:
	FlatStat(std::unique_ptr<MyAction>, const std::string& desc, int hp, int atk, int def, int gold);
	~FlatStat();
	virtual int perform(std::shared_ptr<MyEvent>);
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
	DestructSelf(std::unique_ptr<MyAction>);
	~DestructSelf();
	virtual int perform(std::shared_ptr<MyEvent>);
};

//TransformSelf to 0 without freependinglist
class TrySpend : public MyAction {
public:
	TrySpend(std::unique_ptr<MyAction>, int gold);
	~TrySpend();
	virtual int perform(std::shared_ptr<MyEvent>);
private:
	int gold;
};

class GetKey : public MyAction {
public:
	GetKey(std::unique_ptr<MyAction>, int key, int amount);
	~GetKey();
	virtual int perform(std::shared_ptr<MyEvent>);
private:
	int key;
	int amount;
};