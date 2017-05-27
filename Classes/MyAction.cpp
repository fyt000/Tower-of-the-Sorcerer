#include "MyAction.h"
#include "GameData.h"
#include "Configureader.h"
#include "DialogStruct.h"
#include "GlobalDefs.h"

MyAction::MyAction()
{
}

MyAction::MyAction(MyAction *next) :next(next)
{
}

int MyAction::perform(MyEvent* evt) {
	if (next != nullptr)
		return next->perform(evt);
	return 0;
}

MyAction::~MyAction()
{
	delete next;
}


Talk::Talk(MyAction *next, const std::string& tag) :MyAction(next), tag(tag), type(DIALOGTYPE::NONE)
{
}

int Talk::perform(MyEvent *evt)
{
	showDialog([this, evt](int notUsed)->void {next->perform(evt); });
	return 0;
}

//~MyAction should handle delete next
Talk::~Talk()
{
}

void Talk::showDialog(std::function<void(int)> callback)
{
	std::vector<std::string> dialogStrs;
	Configureader::GetDialog(tag, dialogStrs);
	//there is way too much overhead.... 
	std::queue<DialogStruct> q;
	for (std::size_t i = 0; i < dialogStrs.size(); i++) {

		//handle last one differently
		if (i == dialogStrs.size() - 1) {
			q.emplace(dialogStrs[i], type);
		}
		else
		{
			q.emplace(dialogStrs[i], DIALOGTYPE::NONE);
		}
	}
	if (next == nullptr)
		GameData::getInstance()->showDialog(q, nullptr);
	else
		GameData::getInstance()->showDialog(q, callback);
}

TalkYN::TalkYN(MyAction *action, const std::string& tag) :Talk(action, tag)
{
	type = DIALOGTYPE::YN;
}

int TalkYN::perform(MyEvent *evt)
{
	showDialog([this, evt](int choice)->void {if (choice == 0) next->perform(evt); });
	return 0;
}

TransformSelf::TransformSelf(MyAction *next, int id) :MyAction(next), id(id)
{
}

//the event itself has to handle the destruction
//it will be marked as markedForDeletion
//why do I not delete myself again?
//problem with TransformSelf deleting itself
//1. possible double delete if used on PostEvent (will call selfDestruct)
//2. using the object after TransformSelf deleted itself (other actions followed after TransformSelf)
//3. event gets deleted before dialog completion(async dialogs)!!! this is the most important reason
//	for a NONE type dialog, the person will disappear before mouse click to dismiss dialog
//keep these in mind!
//
int TransformSelf::perform(MyEvent *evt)
{
	//setEvent doesn't free the current occupying event
	GameData::getInstance()->setEvent(id, evt->getX(), evt->getY());
	//it is unsafe to call this without making sure FloorEvent does not have a pointer to evt
	GameData::getInstance()->addToFree(evt);
	MyAction::perform(evt);
	return 1;
}

Obtain::Obtain(MyAction *next, int item) :MyAction(next), item(item)
{
}

int Obtain::perform(MyEvent *evt)
{
	GameData::getInstance()->obtainItem(item);
	MyAction::perform(evt);
	return 0;
}

Transform::Transform(MyAction* next, int floor, int x, int y, int targetID) :MyAction(next), floor(floor), x(x), y(y), targetID(targetID) {
}

int Transform::perform(MyEvent* evt) {
	//if current
	if (GameData::getInstance()->floor->V() == floor) {
		//I am not sure what will happen if you are currently interacting with this event
		//use TransformSelf
		delete GameData::getInstance()->getEvent(x, y);
	}
	GameData::getInstance()->setEvent(targetID, x, y, floor);
	MyAction::perform(evt);
	return 0;
}

LogText::LogText(MyAction *next, const std::string& tag) :MyAction(next), tag(tag)
{
}

int LogText::perform(MyEvent *evt)
{
	GameData::getInstance()->log(GStr(tag));
	MyAction::perform(evt);
	return 0;
}

FlatStat::FlatStat(MyAction* next, const std::string& desc, int hp, int atk, int def, int gold) :MyAction(next), desc(desc), hp(hp), atk(atk), def(def), gold(gold) {
}

int FlatStat::perform(MyEvent *evt)
{
	std::string msg = GStr("consume");
	std::string hpStr;
	std::string atkStr;
	std::string defStr;
	if (hp != 0) {
		hpStr = stdsprintf(GStr("hp_change"), hp);
		GameData::getInstance()->hero->hp.addVal(hp);
	}
	if (atk != 0) {
		hpStr = stdsprintf(GStr("atk_change"), atk);
		GameData::getInstance()->hero->atk.addVal(atk);
	}
	if (def != 0) {
		hpStr = stdsprintf(GStr("def_change"), def);
		GameData::getInstance()->hero->def.addVal(def);
	}
	//remove sword shield images... they are useless
	GameData::getInstance()->log(stdsprintf(msg, desc, hpStr, atkStr, defStr));
	return 0;
}


DestructSelf::DestructSelf(MyAction* next) :MyAction(next) {
}

int DestructSelf::perform(MyEvent* evt) {
	GameData::getInstance()->setEvent(0, evt->getX(), evt->getY());
	MyAction::perform(evt);
	delete evt;
	return 1;
}