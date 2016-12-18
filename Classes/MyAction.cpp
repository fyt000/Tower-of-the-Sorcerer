#include "MyAction.h"
#include "GameData.h"
#include "Configureader.h"
#include "DialogStruct.h"

MyAction::MyAction()
{
}

MyAction::MyAction(MyAction *next):next(next)
{
}

MyAction::~MyAction()
{
	delete next;
}


Talk::Talk(MyAction *next,std::string tag):MyAction(next),tag(tag),type(DIALOGTYPE::NONE)
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

TalkYN::TalkYN(MyAction *action,std::string tag):Talk(action,tag)
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
	if (next!=nullptr)
		next->perform(evt);
	return 1;
}
