#include "MyAction.h"
#include "GameData.h"
#include "Configureader.h"
#include "DialogStruct.h"
#include "GlobalDefs.h"

MyAction::MyAction()
{
}

MyAction::MyAction(MyAction *next):next(next)
{
}

int MyAction::perform(MyEvent* evt){
	if (next!=nullptr)
		return next->perform(evt);
	return 0;
}

MyAction::~MyAction()
{
	delete next;
}


Talk::Talk(MyAction *next,const std::string& tag):MyAction(next),tag(tag),type(DIALOGTYPE::NONE)
{
}

int Talk::perform(MyEvent *evt)
{
	showDialog([this,evt](int notUsed)->void{next->perform(evt);});
	return 0;
}

//~MyAction should handle delete next
Talk::~Talk()
{
}

void Talk::showDialog(std::function<void(int)> callback)
{
	std::vector<std::string> dialogStrs;
	Configureader::GetDialog(tag,dialogStrs);
	//there is way too much overhead.... 
	std::queue<DialogStruct> q;
	for (int i=0;i<dialogStrs.size();i++){
		
		//handle last one differently
		if (i==dialogStrs.size()-1){
			q.emplace(dialogStrs[i],type);
		}
		else
		{
			q.emplace(dialogStrs[i],DIALOGTYPE::NONE);
		}
	}
	if (next==nullptr)
		GameData::getInstance()->showDialog(q,nullptr);
	else
		GameData::getInstance()->showDialog(q,callback);
}

TalkYN::TalkYN(MyAction *action,const std::string& tag):Talk(action,tag)
{
	type=DIALOGTYPE::YN;
}

int TalkYN::perform(MyEvent *evt)
{
	showDialog([this,evt](int choice)->void{if (choice==0) next->perform(evt);});
	return 0;
}

TransformSelf::TransformSelf(MyAction *next,int id):MyAction(next),id(id)
{
}

//the event itself has to handle the destruction
//it will be marked as markedForDeletion
int TransformSelf::perform(MyEvent *evt)
{
	GameData::getInstance()->setEvent(id,evt->getX(),evt->getY());
	//it is unsafe to call this without making sure FloorEvent does not have a pointer to evt
	GameData::getInstance()->addToFree(evt);
	MyAction::perform(evt);
	return 1;
}

Obtain::Obtain(MyAction *next,int item):MyAction(next),item(item)
{
}

int Obtain::perform(MyEvent *evt)
{
	GameData::getInstance()->obtainItem(item);
	MyAction::perform(evt);
	return 0;
}

Transform::Transform(MyAction* next,int floor,int x,int y,int targetID):MyAction(next),floor(floor),x(x),y(y),targetID(targetID){
}

int Transform::perform(MyEvent* evt){
	//if current
	if (GameData::getInstance()->floor->V()==floor){
		//I am not sure what will happen if you are currently interacting with this event
		//use TransformSelf
		delete GameData::getInstance()->getEvent(x,y);
	}
	GameData::getInstance()->setEvent(targetID,x,y,floor);
	MyAction::perform(evt);
	return 0;
}

LogText::LogText(MyAction *next,const std::string& tag):MyAction(next),tag(tag)
{
}

int LogText::perform(MyEvent *evt)
{
	GameData::getInstance()->log(GStr(tag));
	MyAction::perform(evt);
	return 0;
}
