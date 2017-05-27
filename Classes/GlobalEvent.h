#pragma once
#include "MyAction.h"
#include "Condition.h"
#include <vector>

//after every hero action (movement/item usage), check if conditions are met
//if yes, trigger actions
//not exactly global, each floor has its own list of global events that it will check

class GlobalEvent {
public:
	//GlobalEvent(); 
	bool tryTrigger();
	void attachAction(MyAction*);
	void addCondition(Condition*);
	~GlobalEvent();
private:
	std::vector<Condition*> conditions;
	std::vector<MyAction*> actions;
};