#include "Condition.h"
#include "GameData.h"

Condition::Condition(int floor, COND cond, int x, int y) :floor(floor), cond(cond), x(x), y(y)
{
}

bool Condition::check() {
	switch (cond) {
	case COND::EXISTS:
		return GameData::getInstance().getEventID(floor, x, y) != 0;
	case COND::DNE:
		return GameData::getInstance().getEventID(floor, x, y) == 0;
	}
	return false;
}

Condition::~Condition() {}