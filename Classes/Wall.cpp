#include "Wall.h"


Wall::Wall(int imageIdx,std::string desc):MyEvent(imageIdx,desc){
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
