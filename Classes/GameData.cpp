#include "GameData.h"
#include <queue>
#include "Wall.h"
#include "Enemy.h"

static GameData* gameData = nullptr;

//TODO dump this into json/yaml or some other configurable format and read the configuration 
//this will initialize the game data
//this FLOOREVENTS intialization is pretty stupid
//I will change this.
//this must be changed actually, since we can't initialize like this for loading saves
//but that's ok... we can read one by one
GameData::GameData():FLOOREVENTS{ 
	{
		{0} //yes, there is a floor 0
	},
	//floor 1
	{
		{11,0,0,0,0,0,0,0,0,0,0},
		{8,8,8,8,8,8,8,8,8,8,0},
		{32,0,0,0,0,8,0,29,0,8,0},
		{0,77,0,8,0,8,0,32,0,8,0},
		{8,1,8,8,0,8,8,8,1,8,0},
		{29,0,0,8,0,1,67,69,67,8,0},
		{0,79,0,8,0,8,8,8,8,8,0},
		{8,1,8,8,0,0,0,0,0,0,0},
		{0,0,0,8,8,1,8,8,8,1,8},
		{32,0,29,8,29,0,0,8,0,67,0},
		{32,38,29,8,0,0,0,8,61,33,61}
	}},
	FloorEvents{0},
	hero(213,"the 213 hero",1000,15,1,0)
{
	EVENTDATA[0]=NULL;
	EVENTDATA[1]=new MyEvent(1,"yellow door");
	EVENTDATA[8]=new Wall(8,"wall");
	EVENTDATA[11]=new MyEvent(11,"upstairs"); //?
	EVENTDATA[29]=new MyEvent(29,"yellow key");
	EVENTDATA[32]=new MyEvent(32,"red exlixir");
	EVENTDATA[33]=new MyEvent(33,"blue exlixir");
	EVENTDATA[38]=new MyEvent(38,"special item no3");

	EVENTDATA[61]=new Enemy(61,"Green Slime",62,35,18,1,1);
	EVENTDATA[67]=new Enemy(67,"Bat",68,35,38,3,1);
	EVENTDATA[69]=new Enemy(69,"Priest",70,60,32,8,1);
	EVENTDATA[77]=new Enemy(77,"Skeleton C",78,50,42,6,1);
	EVENTDATA[79]=new Enemy(79,"Skeleton B",80,55,52,12,1);

	floor=1;

	loadFloor();
}

//kinda singleton
GameData* GameData::getInstance(){
	if (!gameData){
		gameData=new GameData();
	}
	return gameData;
}

MyEvent * GameData::getEvent(int x,int y)
{
	return FloorEvents[floor][x][y];
}

//get event pointer given the id
MyEvent * GameData::getEventData(int id)
{
	if (id<0||id>=500){ //?
		return NULL;
	}
	return EVENTDATA[id];
}

//get event based on the location of the current floor
MyEvent * GameData::getEventData(int x,int y)
{
	return getEventData(FLOOREVENTS[floor][x][y]);
}

void GameData::loadFloor(){
	int curFloor=floor;
	for (int k=0;k<MAXFLOOR;k++){
		floor=k;
		for (int i=0;i<11;i++)
			for (int j=0;j<11;j++){
				delete FloorEvents[k][i][j]; //if I call loadFloor on loading save files
				FloorEvents[k][i][j]=NULL;
				MyEvent* event=getEventData(i,j);
				if (event){
					FloorEvents[k][i][j]=event->clone();
					FloorEvents[k][i][j]->setXY(i,j);
				}
			}
	}
	floor=curFloor;
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

cocos2d::Sprite * GameData::getSprite(int x,int y)
{
	if (!FloorEvents[floor][x][y])
		return nullptr;
	return FloorEvents[floor][x][y]->getSprite();
}


/*
void GameData::moveHero(PATH path)
{
	//floorMouseListener->setEnabled(false);
	if (path.size()==0)
		return;
	hero.move(path);
	//Director::getInstance()->getEventDispatcher()->setEnabled(false);
}
*/
//this method is only being called from FloorScene
//no one else should call this
void GameData::moveHero(std::pair<int,int> dest){
	logLable->setVisible(false);
	logLable->setString("");
	auto eventPtr=getEvent(dest.first,dest.second);
	if (eventPtr==NULL){//check if it is an event
		hero.move(pathFind(dest),true);
	}
	else{
		hero.move(pathFind(dest));
		//moveHero(pathFind(dest));
	}
}
/*
void GameData::moveAndTriggerStepOnEvent(std::pair<int,int> dest,std::function<void> hpCallback1){

}*/

void GameData::killEvent(std::pair<int,int> place){
	auto eventPtr=getEvent(place.first,place.second);
	if (eventPtr){
		FloorEvents[floor][place.first][place.second]=NULL;
		delete eventPtr;
	}
}

void GameData::moveHeroFinalStep(std::pair<int,int> dest){
	auto eventPtr=getEvent(dest.first,dest.second);
	if (eventPtr==NULL){//check if it is an event
		//do single move if nothing will happen
		hero.move(dest);
		return;
	}
	
	//check if distance is 1
	if ((dest.first==hero.getX()&&abs(hero.getY()-dest.second)==1)||
		(dest.second==hero.getY()&&abs(hero.getX()-dest.first)==1)){
		if (eventPtr->triggerEvent()){
			hero.move(pathFind(dest),true);
			/*
			if (!eventPtr->stepOnEvent())
				Director::getInstance()->getEventDispatcher()->setEnabled(true);*/
			/*
			FloorEvents[floor][dest.first][dest.second]=NULL;
			delete eventPtr;*/
		}
		else{
			Director::getInstance()->getEventDispatcher()->setEnabled(true);
		}
	}
	else{
		//else do a path find and move to the place
		//moveHero(pathFind(dest));
		hero.move(pathFind(dest));
	}
	
}

PATH GameData::pathFind(std::pair<int,int> dest){
	return pathFind(dest.first,dest.second);
}

//find a path from the current location (heroX,heroY) to the specified path
//use simple bfs will gurantee shortest path, since distance between each block is always 1
//this is called if the destination is not an event
//change to accept 1 obstacle.
PATH GameData::pathFind(int dx,int dy)
{

	if (dx==-1||dy==-1||hero.getX()==dx&&hero.getY()==dy){
		return std::vector<std::pair<int,int>>(); //do nothing
	}

	//||getEvent(dx,dy)

	int vis[11][11]={0};
	vis[hero.getX()][hero.getY()]=1;
	std::vector<std::pair<int,int> > path;

	std::vector<std::pair<int,int> > bfsQ;
	std::vector<int> parent;

	//for every bfsQ push, we need a parent push
	bfsQ.push_back(std::pair<int,int>(hero.getX(),hero.getY()));
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
				auto event=getEvent(newX,newY);
				if (!event||(newX==dx&&newY==dy)){ //can only walk on NULL, do not try to trigger on any event
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
		path.pop_back(); //this is just the src loc
		std::reverse(path.begin(),path.end());
		path.push_back(std::pair<int,int>(dx,dy)); //push destination to the path.
	}
	return path;
}

void GameData::log(std::string message,bool inst)
{
	CCLOG("log message: %s",message);
	logLable->setString(message);
	logLable->setVisible(inst);
	if (inst){
		logLable->setOpacity(0);
		logLable->runAction(FadeIn::create(0.75));
	}
}

void GameData::showLog(){
	if (logLable->isVisible()){
		return;
	}
	logLable->setVisible(true);	
	if (logLable->getString()!=""){
		logLable->setOpacity(0);
		logLable->runAction(FadeIn::create(0.75));
	}

}

GameData::~GameData(){
	//closing the app will clean up everything.
}
