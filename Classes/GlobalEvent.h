#pragma once
#include "MyAction.h"
#include "Condition.h"
#include <vector>
#include <memory>

//after every hero action (movement/item usage), check if conditions are met
//if yes, trigger actions
//not exactly global, each floor has its own list of global events that it will check

class GlobalEvent {
public:
	GlobalEvent(int id); 
	bool tryTrigger();
	void attachAction(std::unique_ptr<MyAction>);
	void addCondition(std::unique_ptr<Condition>);
	int getId();
	~GlobalEvent();
private:
	int id;
	std::vector<std::unique_ptr<Condition>> conditions;
	std::vector<std::unique_ptr<MyAction>> actions;
};