#pragma once
#include <string>
#include <functional>
#include "GlobalDefs.h"
//action carries out an action that is attached to a event
//aside from very few things, events do not have a state, you `Transform' into another event

class MyEvent;

class MyAction{
public:
	MyAction();
	MyAction(MyAction*);
	virtual int perform(MyEvent*);
	virtual ~MyAction();
protected:
	//action chaining
	MyAction* next;
};


class Obtain:public MyAction{
public:
	Obtain(MyAction*,int item); //TODO make items
	int perform(MyEvent*);
private:
	int item;
};

class Talk: public MyAction{
public:
	Talk(MyAction*,const std::string& tag);
	virtual int perform(MyEvent*);
	virtual ~Talk();
protected:
	void showDialog(std::function<void(int)>);
	std::string tag;
	enum DIALOGTYPE type;
};

class TalkYN: public Talk{
public:
	TalkYN(MyAction*,const std::string& tag);
	virtual int perform(MyEvent*);
};

class TransformSelf: public MyAction{
public:
	TransformSelf(MyAction*,int id);
	virtual int perform(MyEvent*);
private:
	int id;
};

//TODO add animation type?
class Transform: public MyAction{
public:
	Transform(MyAction*,int floor,int x,int y,int targetID);
	virtual int perform(MyEvent*);
private:
	int floor;
	int x;
	int y;
	int targetID;
};

class LogText: public MyAction{
public:
	LogText(MyAction*,const std::string& tag);
	virtual int perform(MyEvent*);
private:
	std::string tag;
};