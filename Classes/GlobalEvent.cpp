#include "GlobalEvent.h"
#include <vector>

GlobalEvent::GlobalEvent(int id) : id(id) {}

bool GlobalEvent::tryTrigger() {
	for (auto& cond : conditions) {
		if (!cond->check())
			return false;
	}
	for (size_t i = 0; i < actions.size(); i++)
		actions[i]->perform(nullptr);
	return true;
}

void GlobalEvent::attachAction(std::unique_ptr<MyAction> action) {
	// probably auto moved
	actions.push_back(std::move(action));
}

void GlobalEvent::addCondition(std::unique_ptr<Condition> cond) {
	conditions.push_back(std::move(cond));
}

int GlobalEvent::getId() {
	return id;
}

GlobalEvent::~GlobalEvent() {
}