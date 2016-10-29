#include "GameData.h"
#include <queue>

static GameData* gameData = nullptr;

//TODO dump this into json/yaml or some other configurable format and read the configuration 
//this will initialize the game data
//this FLOOREVENTS intialization is pretty stupid
//I will change this.
GameData::GameData():FLOOREVENTS{
	{
		{0}
	},
	//floor 1
	{
		{11,0,0,0,0,0,0,0,0,0,0},
		{8,8,8,8,8,8,8,8,8,8,0},
		{32,0,0,1,0,8,0,29,0,8,0},
		{0,77,0,8,0,8,0,32,0,8,0},
		{8,1,8,8,0,8,8,8,1,8,0},
		{29,0,0,8,0,1,67,69,67,8,0},
		{0,79,0,8,0,8,8,8,8,8,0},
		{8,1,8,8,0,0,0,0,0,0,0},
		{0,0,0,8,8,1,8,8,8,1,8},
		{32,0,29,8,29,0,0,8,0,67,0},
		{32,38,29,8,0,0,0,8,61,33,61}
	}}
{
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

	heroX=7;heroY=4;

}

//kinda singleton
GameData* GameData::getInstance(){
	if (!gameData){
		gameData=new GameData();
	}
	return gameData;
}

//get event pointer given the id
MyEvent * GameData::getEventData(int id)
{
	if (id<0||id>=500){
		return NULL;
	}
	return EVENTDATA[id];
}

//get event based on the location of the current floor
MyEvent * GameData::getEventData(int x,int y)
{
	return getEventData(FLOOREVENTS[floor][x][y]);
}




int GameData::goUpStairs()
{
	floor++;
	return floor;
}

int GameData::goDownStairs()
{
	floor--;
	return floor;
}

int GameData::setFloor(int f){
	floor=f;
	return floor;
}

cocos2d::Sprite * GameData::getSprite(int x,int y,int px,int py)
{
	auto curFloor=FLOOREVENTS[floor];
	if (!curFloor[x][y])
		return nullptr;
	return getEventData(curFloor[x][y])->getSprite(px,py);
}

std::vector<std::pair<int,int>> GameData::pathFind(std::pair<int,int> dest){
	return pathFind(dest.first,dest.second);
}

//find a path from the current location (heroX,heroY) to the specified path
//use simple bfs will gurantee shortest path, since distance between each block is always 1
//this is called if the destination is not an event
std::vector<std::pair<int,int>> GameData::pathFind(int dx,int dy)
{

	if (dx==-1||dy==-1||heroX==dx&&heroY==dy||getEventData(dx,dy)){ 
		return std::vector<std::pair<int,int>>(); //do nothing
	}

	int vis[11][11]={0};
	vis[heroX][heroY]=1;
	std::vector<std::pair<int,int> > path;

	std::vector<std::pair<int,int> > bfsQ;
	std::vector<int> parent;

	//for every bfsQ push, we need a parent push
	bfsQ.push_back(std::pair<int,int>(heroX,heroY));
	parent.push_back(-1); //no parent for the root
	int idx=0;

	const int dirX[]={1,0,-1,0};
	const int dirY[]={0,1,0,-1};
	int found=0;
	while (idx!=bfsQ.size()){
		auto curPos = bfsQ[idx];
		for (int i=0;i<4;i++){
			int newX=dirX[i]+curPos.first;
			int newY=dirY[i]+curPos.second;
			if (newX>=0&&newX<11&&newY>=0&&newY<11&&!vis[newX][newY]){
				auto event=getEventData(newX,newY);
				if (!event){ //can only walk on NULL, do not try to trigger on any event
					//this could give away 'hidden' events... so ok we could add an extra parameter or something I don't know
					bfsQ.push_back(std::pair<int,int>(newX,newY));
					parent.push_back(idx);
					vis[newX][newY]=1;
					if (newX==dx&&newY==dy){
						found=1;
						break;
					}
				}
			}
		}
		if (found)
			break;
		idx++;
	}
	if (found){
		auto prev=parent.back();  //this is the destination
		while (prev!=-1){
			path.push_back(bfsQ[prev]);
			prev=parent[prev];
		}
		//we could do recursion to flip the vector
		//but I don't want another method just to do this
		std::reverse(path.begin(),path.end());
	}
	return path;
}




GameData::~GameData(){
	//closing the app will clean up everything.
}
