#include "Wall.h"


Wall::Wall(int id,std::string desc):MyEvent(id,desc){
}

bool Wall::triggerEvent()
{
	return false;
}

Wall * Wall::clone()
{
	return new Wall(*this);
}

Wall::
~Wall()
{
}
