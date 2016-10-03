#include "GameData.h"

static GameData* gameData = nullptr;


GameData::GameData(){
	EVENTDATA[0]=NULL;
	EVENTDATA[1]=new MyEvent(1,"yellow door");
	EVENTDATA[8]=new MyEvent(8,"wall");
	EVENTDATA[11]=new MyEvent(11,"upstairs"); //?
	EVENTDATA[29]=new MyEvent(29,"yellow key");
	EVENTDATA[32]=new MyEvent(32,"red exlixir");
	EVENTDATA[33]=new MyEvent(33,"blue exlixir");
	EVENTDATA[38]=new MyEvent(38,"special item no3");

	EVENTDATA[61]=new Enemy(61,"Green Slime",62,35,18,1);
	EVENTDATA[67]=new Enemy(67,"Bat",68,35,38,3);
	EVENTDATA[69]=new Enemy(69,"Priest",70,60,32,8);
	EVENTDATA[77]=new Enemy(77,"Skeleton C",78,50,42,6);
	EVENTDATA[79]=new Enemy(79,"Skeleton B",80,55,52,12);

}

GameData* GameData::getInstance(){
	if (!gameData){
		gameData=new GameData();
	}
	return gameData;
}

MyEvent * GameData::getEventData(int id)
{
	if (id<0||id>=500){
		return NULL;
	}
	return EVENTDATA[id];
}

GameData::~GameData(){

}
