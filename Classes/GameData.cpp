#include "GameData.h"
#include <queue>
#include "Wall.h"
#include "Enemy.h"
#include "Consumable.h"
#include "Door.h"
#include "Configureader.h"
#include "DialogStruct.h"

USING_NS_CC;

static GameData* gameData = nullptr;

//TODO dump this into json/yaml or some other configurable format and read the configuration 
//this will initialize the game data
//this FLOOREVENTS intialization is pretty stupid
//I will change this.
//this must be changed actually, since we can't initialize like this for loading saves
//but that's ok... we can read one by one
GameData::GameData(){
	init();
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
	return FloorEvents[x][y];
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
	return getEventData(FLOOREVENTS[floor->V()][x][y]);
}

void GameData::showDialog(std::queue<DialogStruct>& dq,std::function<void(int)> callback)
{
	dialogCallback=callback; //always override callback...to make life simple
	//10 thousand string copying going around
	//need to fix this
	if (dialogQ.empty())
		dialogQ=dq; //make a copy
	else{
		while (!dq.empty()){
			dialogQ.push(dq.front());
			dq.pop();
		}
		return;
	}
	
	if (dialogQ.size()!=0){
		DialogStruct& ds=dialogQ.front();
		flScn->drawDialog(ds.text,ds.dialogType,ds.options);
		dialogQ.pop();
	}
}

void GameData::showDialog(DialogStruct& ds,std::function<void(int)> callback)
{
	dialogQ=std::queue<DialogStruct>(); //empty
	dialogCallback=callback;
	flScn->drawDialog(ds.text,ds.dialogType,ds.options);
}

void GameData::dialogCompleted(int choice)
{
	if (!dialogQ.empty()){
		DialogStruct& ds=dialogQ.front();
		flScn->drawDialog(ds.text,ds.dialogType,ds.options);
		dialogQ.pop();
	}
	else{
		if (dialogCallback!=nullptr)
			dialogCallback(choice);
	}
	GameData::getInstance()->freePendingFreeList();
}

void GameData::init()
{
	hero = new HeroX(213,"hahaha",10,10,10,0);
	floor = new LabelBinder<int>(1);

	Configureader::ReadEventData(EVENTDATA,EVENT_MAX);
	Configureader::ReadFloorEvents(FLOOREVENTS,MAXFLOOR,11,11);

	loadFloor(1);
}


void GameData::gameover()
{
	Director::getInstance()->getEventDispatcher()->setEnabled(true);
	showDialog(DialogStruct(GStr("gameover"),DIALOGTYPE::NONE),[this](int notUsed)->void{
		gameData=nullptr;
		delete this;
		Director::getInstance()->popScene();
	});

}

void GameData::addToFree(MyEvent *evt)
{
	freeListLock.lock();
	pendingFreeList.push_back(evt);
	freeListLock.unlock();
}

void GameData::freePendingFreeList()
{
	freeListLock.lock();
	for (int i=0;i<pendingFreeList.size();i++){
		delete pendingFreeList[i];
	}
	pendingFreeList=std::vector<MyEvent*>();
	freeListLock.unlock();
}

void GameData::attachEnemyInfo(Enemy * enemy)
{
	enemy->hp.attach(eHpLabel);
	enemy->atk.attach(eAtkLabel);
	enemy->def.attach(eDefLabel);
	eDescLabel->setString(enemy->getDescription());
	auto sprite=enemy->getSprite(true);
	flScn->drawEnemyPortrait(sprite);
}


void GameData::loadFloor(int nextFloor){
	floor->setVal(nextFloor);
	for (int i=0;i<11;i++)
		for (int j=0;j<11;j++){
			delete FloorEvents[i][j]; //if I call loadFloor on loading save files
			FloorEvents[i][j]=NULL;
			MyEvent* event=getEventData(i,j);
			if (event){
				FloorEvents[i][j]=event->clone();
				FloorEvents[i][j]->setXY(i,j);
			}
		}
}


int GameData::setFloor(int f){
	loadFloor(f);
	flScn->loadFloor();
	floorChange=true;
	return floor->V();
}

cocos2d::Sprite * GameData::getSprite(int x,int y)
{
	if (!FloorEvents[x][y])
		return nullptr;
	return FloorEvents[x][y]->getSprite();
}


/*
void GameData::moveHero(PATH path)
{
	//floorMouseListener->setEnabled(false);
	if (path.size()==0)
		return;
	hero->move(path);
	//Director::getInstance()->getEventDispatcher()->setEnabled(false);
}
*/
//this method is only being called from FloorScene
//no one else should call this
void GameData::moveHero(std::pair<int,int> dest){
	logLabel->setVisible(false);
	logLabel->setString("");
	auto eventPtr=getEvent(dest.first,dest.second);
	if (eventPtr==NULL){//check if it is an event
		hero->move(pathFind(dest),true);
	}
	else{
		hero->move(pathFind(dest));
		//moveHero(pathFind(dest));
	}
}


void GameData::killEvent(std::pair<int,int> place){
	auto eventPtr=getEvent(place.first,place.second);
	if (eventPtr){
		FLOOREVENTS[floor->V()][place.first][place.second]=0;
		FloorEvents[place.first][place.second]=NULL;
		delete eventPtr;
	}
}

//do not destruct the current occupying event
void GameData::setEvent(int id,int x,int y,int f)
{
	if (f==-1)
		f=floor->V();
	FLOOREVENTS[floor->V()][x][y]=id;
	if (f==floor->V()){
		FloorEvents[x][y]=getEventData(id);
	}
	//reload floor
	//flScn->loadFloor();
}

void GameData::moveHeroFinalStep(std::pair<int,int> dest){
	auto eventPtr=getEvent(dest.first,dest.second);
	if (eventPtr==NULL){//check if it is an event
		//do single move if nothing will happen
		hero->move(dest);
		return;
	}
	
	//check if distance is 1
	if ((dest.first==hero->getX()&&abs(hero->getY()-dest.second)==1)||
		(dest.second==hero->getY()&&abs(hero->getX()-dest.first)==1)){
		if (eventPtr->triggerEvent()){
			hero->move(pathFind(dest),true);
		}
		else{
			if (!floorChange){
				hero->changeFacingDir(dest);
			}
			else
			{
				floorChange=false;
			}
			Director::getInstance()->getEventDispatcher()->setEnabled(true);
		}
	}
	else{
		//else do a path find and move to the place
		//moveHero(pathFind(dest));
		hero->move(pathFind(dest));
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

	if (dx==-1||dy==-1||hero->getX()==dx&&hero->getY()==dy){
		return std::vector<std::pair<int,int>>(); //do nothing
	}

	//||getEvent(dx,dy)

	int vis[11][11]={0};
	vis[hero->getX()][hero->getY()]=1;
	std::vector<std::pair<int,int> > path;

	std::vector<std::pair<int,int> > bfsQ;
	std::vector<int> parent;

	//for every bfsQ push, we need a parent push
	bfsQ.push_back(std::pair<int,int>(hero->getX(),hero->getY()));
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

void GameData::log(std::string& message,bool inst)
{
	CCLOG("log message: %s",message);
	logLabel->setString(message);
	logLabel->setVisible(inst);
	if (inst){
		logLabel->setOpacity(0);
		logLabel->runAction(FadeIn::create(0.75));
	}
}

void GameData::showLog(){
	if (logLabel->isVisible()){
		return;
	}
	logLabel->setVisible(true);	
	if (logLabel->getString()!=""){
		logLabel->setOpacity(0);
		logLabel->runAction(FadeIn::create(0.75));
	}

}

GameData::~GameData(){
	freePendingFreeList();
	//closing the app will clean up everything.
	delete hero;
	hero=nullptr;
	delete floor;
	floor=nullptr;
	for (int i=0;i<11;i++)
		for (int j=0;j<11;j++){
			delete FloorEvents[i][j]; //if I call loadFloor on loading save files
			FloorEvents[i][j]=NULL;
		}
	for (int i=0;i<MAXEVENT;i++){
		delete EVENTDATA[i];
		EVENTDATA[i]=NULL;
	}
	
}
