#pragma once
#include <string>
#include <memory>
#include "cocos2d.h"
#include "MyAction.h"

// enable_shared_from_this required to pass the object for performActions
class MyEvent : std::enable_shared_from_this<MyEvent>
{
public:
	MyEvent(int imageIdx, const std::string& decription);
	MyEvent(int imageIdx, const std::string& decription, int imageIdx2);

	virtual ~MyEvent();
	void setXY(int x, int y);

	//the description stored is actually the decription tag
	//this returns the actual string
	std::string getDescription();

	//create new to create a seprate sprite
	virtual cocos2d::Sprite* getSprite(bool createNew = false);

	//called before hero steps on the event
	//true - yes you can step on it
	//false - hero cannot step on it
	//actions are performed here
	virtual bool triggerEvent();
	//triggered after stepping on the event
	virtual bool stepOnEvent();
	virtual int getX();
	virtual int getY();
	void attachAction(std::unique_ptr<MyAction>);
	int performActions();

	cocos2d::Sprite* sprite = nullptr;

protected:
	int imageIdx;
	int imageIdx2 = -1;
	int x;
	int y;

	void selfDestruct();

private:
	std::string description;
	std::vector<std::unique_ptr<MyAction>> actions;
};
