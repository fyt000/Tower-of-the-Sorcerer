#include "Floor.h"
#include "GameData.h"


Floor::Floor(int floorEvents[11*11])
{
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			cells[i][j]=GameData::getInstance()->getEventData(floorEvents[i*11+j]);
		}
	}
}


Floor::~Floor()
{
}
