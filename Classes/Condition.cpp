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
	case COND::AT:
		return
			GameData::getInstance().floor->V() == floor &&
			GameData::getInstance().hero->getX() == x &&
			GameData::getInstance().hero->getY() == y;
	}
	return false;
}

Condition::~Condition() {}