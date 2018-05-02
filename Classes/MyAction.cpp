#include "MyAction.h"
#include "GameData.h"
#include "Configureader.h"
#include "DialogStruct.h"
#include "GlobalDefs.h"

using namespace twsutil;

MyAction::MyAction()
{
}

MyAction::MyAction(std::unique_ptr<MyAction> next) : next(std::move(next))
{
}

int MyAction::perform(std::shared_ptr<MyEvent> evt) {
	if (next != nullptr)
		return next->perform(evt);
	return 0;
}

MyAction::~MyAction()
{
}


Talk::Talk(std::unique_ptr<MyAction> next, const std::string& tag) : 
	MyAction(std::move(next)), tag(tag), type(DIALOGTYPE::NONE)
{
}

int Talk::perform(std::shared_ptr<MyEvent> evt)
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
	// I feel this is going to be quite dangerous
	// [this, evt] may not exist.
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
		GameData::getInstance().showDialog(q, nullptr);
	else
		GameData::getInstance().showDialog(q, callback);
}

TalkYN::TalkYN(std::unique_ptr<MyAction> action, const std::string& tag) :Talk(std::move(action), tag)
{
	type = DIALOGTYPE::YN;
}

TalkYN::~TalkYN()
{
}

int TalkYN::perform(std::shared_ptr<MyEvent> evt)
{
	showDialog([this, evt](int choice)->void {if (choice == 0) next->perform(evt); });
	return 0;
}

TransformSelf::TransformSelf(std::unique_ptr<MyAction> next, int id) : MyAction(std::move(next)), id(id)
{
}

TransformSelf::~TransformSelf()
{
}

// I am attempting to use shared_ptr to solve all of my deleting shenanigans
// Transform should work exactly as TransformSelf after the fix
int TransformSelf::perform(std::shared_ptr<MyEvent> evt)
{
	//setEvent doesn't free the current occupying event
	GameData::getInstance().setEvent(id, evt->getX(), evt->getY());
	// shared_ptr!
	//it is unsafe to call this without making sure FloorEvent does not have a pointer to evt
	// GameData::getInstance()->addToFree(evt);
	MyAction::perform(evt);
	return 1; // ?
}

Obtain::Obtain(std::unique_ptr<MyAction> next, int item) : MyAction(std::move(next)), item(item)
{
}

Obtain::~Obtain()
{
}

int Obtain::perform(std::shared_ptr<MyEvent> evt)
{
	GameData::getInstance().obtainItem(item);
	MyAction::perform(evt);
	return 0;
}

Transform::Transform(std::unique_ptr<MyAction> next, int floor, int x, int y, int targetID) : 
	MyAction(std::move(next)), floor(floor), x(x), y(y), targetID(targetID) {
}

Transform::~Transform()
{
}

int Transform::perform(std::shared_ptr<MyEvent> evt) {
	GameData::getInstance().setEvent(targetID, x, y, floor);
	MyAction::perform(evt);
	return 0; // ?
}

LogText::LogText(std::unique_ptr<MyAction> next, const std::string& tag) : MyAction(std::move(next)), tag(tag)
{
}

LogText::~LogText()
{
}

int LogText::perform(std::shared_ptr<MyEvent> evt)
{
	GameData::getInstance().log(GStr(tag));
	MyAction::perform(evt);
	return 0;
}

FlatStat::FlatStat(std::unique_ptr<MyAction> next, const std::string& desc, int hp, int atk, int def, int gold) :
	MyAction(std::move(next)), desc(desc), hp(hp), atk(atk), def(def), gold(gold) {
}

FlatStat::~FlatStat()
{
}

int FlatStat::perform(std::shared_ptr<MyEvent> evt)
{
	std::string msg = GStr("consume");
	std::string hpStr;
	std::string atkStr;
	std::string defStr;
	std::string goldStr;
	if (hp != 0) {
		hpStr = stdsprintf(GStr("hp_change"), hp);
		GameData::getInstance().hero->hp.addVal(hp);
	}
	if (atk != 0) {
		hpStr = stdsprintf(GStr("atk_change"), atk);
		GameData::getInstance().hero->atk.addVal(atk);
	}
	if (def != 0) {
		hpStr = stdsprintf(GStr("def_change"), def);
		GameData::getInstance().hero->def.addVal(def);
	}
	if (gold != 0) {
		goldStr = stdsprintf(GStr("get_gold"), gold);
		GameData::getInstance().hero->gold.addVal(gold);
	}
	GameData::getInstance().log(stdsprintf(msg, desc, hpStr, atkStr, defStr, goldStr));
	MyAction::perform(evt);
	return 0;
}


DestructSelf::DestructSelf(std::unique_ptr<MyAction> next) : MyAction(std::move(next)) {
}

DestructSelf::~DestructSelf()
{
}

int DestructSelf::perform(std::shared_ptr<MyEvent> evt) {
	GameData::getInstance().setEvent(0, evt->getX(), evt->getY());
	MyAction::perform(evt);
	return 1;
}

TrySpend::TrySpend(std::unique_ptr<MyAction> next, int gold) : MyAction(std::move(next)), gold(gold)
{
}

TrySpend::~TrySpend()
{
}

int TrySpend::perform(std::shared_ptr<MyEvent> evt)
{
	if (GameData::getInstance().hero->spendGold(gold))
		MyAction::perform(evt);
	else
		GameData::getInstance().log(GStr("not_enough_gold"));
	return 0;
}

GetKey::GetKey(std::unique_ptr<MyAction> next, int key, int amount) : MyAction(std::move(next)), key(key), amount(amount)
{
}

GetKey::~GetKey()
{
}

int GetKey::perform(std::shared_ptr<MyEvent> evt)
{
	if (amount > 1)
		GameData::getInstance().log(stdsprintf(GStr("get_keys"), amount, GStr("key_" + std::to_string(key))));
	else
		GameData::getInstance().log(stdsprintf(GStr("get_key"), GStr("key_" + std::to_string(key))));
	GameData::getInstance().keys[key]->addVal(amount);
	MyAction::perform(evt);
	return 0;
}

