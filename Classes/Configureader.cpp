#include "Configureader.h"
#include "MyEvent.h"
#include "cocos2d.h"
#include "Wall.h"
#include "Enemy.h"
#include "Consumable.h"
#include "Door.h"
#include "Key.h"
#include "Stairs.h"
#include "MyAction.h"
#include "HeroItem.h"
#include "Condition.h"
#include "GlobalEvent.h"
#include "GlobalDefs.h"
#include "Shop.h"
#include "PostEvent.h"
#include <unordered_map>

using namespace twsutil;

std::unique_ptr<rapidjson::Document> Configureader::langStrDoc = nullptr;
std::unique_ptr<rapidjson::Document> Configureader::dataDoc = nullptr;
std::string Configureader::curLanguageFile = "res/res_english.json";
std::unordered_map<int, int> Configureader::eventIdxMapping;

std::unique_ptr<MyEvent> Configureader::getEvent(int id)
{
	int maxEvent = MAXEVENT;

	if (dataDoc == nullptr) {
		initDataDoc();
	}

	int resultIdx = -1;
	auto iter = eventIdxMapping.find(id);
	if (iter == eventIdxMapping.end()) {
		// linear search
		rapidjson::Value& eventdata = (*dataDoc)["eventdata"];
		for (rapidjson::SizeType i = 0; i < eventdata.Size(); i++) {
			auto& data = eventdata[i];
			int idx = data["id"].GetInt();
			std::string type = data["type"].GetString();
			rapidjson::Value& p = data["params"];
			if (idx >= maxEvent)
				continue;
			if (idx == id) {
				// cache result
				resultIdx = i;
				eventIdxMapping[id] = i;
				break;
			}
		}
	}
	else {
		resultIdx = iter->second;
	}

	if (resultIdx == -1) return nullptr;
	
	rapidjson::Value& eventdata = (*dataDoc)["eventdata"];
	auto& data = eventdata[resultIdx];
	int idx = data["id"].GetInt();
	std::string type = data["type"].GetString();
	rapidjson::Value& p = data["params"];

	std::unique_ptr<MyEvent> event = nullptr;

	if (type == "Door") {
		event = std::make_unique<Door>(p[0].GetInt(), p[1].GetString(), static_cast<KeyType>(p[2].GetInt()));
	}
	else if (type == "Wall") {
		event = std::make_unique<Wall>(p[0].GetInt(), p[1].GetString());
	}
	else if (type == "MyEvent") {
		if (p.Size() == 2)
			event = std::make_unique<MyEvent>(p[0].GetInt(), p[1].GetString());
		else
			event = std::make_unique<MyEvent>(p[0].GetInt(), p[1].GetString(), p[2].GetInt());
	}
	else if (type == "Key") {
		event = std::make_unique<Key>(p[0].GetInt(), p[1].GetString(), static_cast<KeyType>(p[2].GetInt()));
	}
	else if (type == "Consumable") {
		event = std::make_unique<Consumable>(p[0].GetInt(), p[1].GetString(), p[2].GetInt(), p[3].GetInt(), p[4].GetInt(), p[5].GetInt());
	}
	else if (type == "Enemy") {
		event = std::make_unique<Enemy>(p[0].GetInt(), p[1].GetString(), p[2].GetInt(), p[3].GetInt(), p[4].GetInt(), p[5].GetInt(), p[6].GetInt());
	}
	else if (type == "Stairs") {
		event = std::make_unique<Stairs>(p[0].GetInt(), p[1].GetString(), p[2].GetInt(), p[3].GetInt(), p[4].GetInt(), static_cast<DIR>(p[5].GetInt()));
	}
	else if (type == "Shop") {
		event = std::make_unique<Shop>(p[0].GetInt(), p[1].GetString(), p[2].GetInt(), p[3].GetInt(), p[4].GetInt(), p[5].GetInt());
	}
	else if (type == "PostEvent") {
		if (p.Size() == 2)
			event = std::make_unique<PostEvent>(p[0].GetInt(), p[1].GetString());
		else
			event = std::make_unique<PostEvent>(p[0].GetInt(), p[1].GetString(), p[2].GetInt());
	}

	if (event) {
		auto actions = data.FindMember("actions");
		if (actions != data.MemberEnd()) {
			rapidjson::Value& actionsData = actions->value;
			for (rapidjson::SizeType j = 0; j < actionsData.Size(); j++) {
				event->attachAction(getAction(actionsData[j]));
			}
		}
	}

	return event;
}

std::unique_ptr<MyAction> Configureader::getAction(rapidjson::Value &data)
{

	std::unique_ptr<MyAction> next = nullptr;
	auto nextData = data.FindMember("next");
	if (nextData != data.MemberEnd()) {
		next = getAction(nextData->value);
	}
	std::string type = data["action"].GetString();
	if (type == "Talk") {
		return std::make_unique<Talk>(std::move(next), data["tag"].GetString());
	}
	else if (type == "TalkYN") {
		return std::make_unique<TalkYN>(std::move(next), data["tag"].GetString());
	}
	else if (type == "TransformSelf") {
		return std::make_unique<TransformSelf>(std::move(next), data["new"].GetInt());
	}
	else if (type == "Obtain") {
		return std::make_unique<Obtain>(std::move(next), data["id"].GetInt());
	}
	else if (type == "LogText") {
		return std::make_unique<LogText>(std::move(next), data["tag"].GetString());
	}
	else if (type == "Transform") {
		return std::make_unique<Transform>(std::move(next), data["floor"].GetInt(), data["x"].GetInt(), data["y"].GetInt(), data["id"].GetInt());
	}
	else if (type == "FlatStat") {
		return std::make_unique<FlatStat>(std::move(next), GStr(data["description"].GetString()), data["hp"].GetInt(), data["atk"].GetInt(), data["def"].GetInt(), data["gold"].GetInt());
	}
	else if (type == "DestructSelf") {
		return std::make_unique<DestructSelf>(std::move(next));
	}
	return nullptr;
}


void Configureader::ReadFloorEvents(int FloorArr[][11][11])
{
	int maxFloor = MAXFLOOR;
	int maxx = 11;
	int maxy = 11;
	if (dataDoc == nullptr) {
		initDataDoc();
	}
	rapidjson::Value& floorevent = (*dataDoc)["floorevents"];

	for (rapidjson::SizeType i = 0; i < floorevent.Size(); i++) {
		int idx = floorevent[i]["floor"].GetInt();
		if (idx > maxFloor)
			continue;
		for (int x = 0; x < maxx; x++) {
			for (int y = 0; y < maxy; y++) {
				FloorArr[idx][x][y] = floorevent[i]["data"][x][y].GetInt();
			}
		}
	}
	return;
}

void Configureader::ReadItemData(std::unique_ptr<HeroItem>*itemArr)
{
	int maxItem = MAXITEMS;
	if (dataDoc == nullptr) {
		initDataDoc();
	}
	rapidjson::Value& itemdata = (*dataDoc)["items"];
	for (rapidjson::SizeType i = 0; i < itemdata.Size(); i++) {
		auto& data = itemdata[i];
		int idx = data["id"].GetInt();
		if (idx >= maxItem)
			continue;
		itemArr[idx] = std::make_unique<HeroItem>(idx, data["name"].GetString(), data["image"].GetInt(),
												  HeroItem::getEffectFunction(data["effect"].GetString()), 
												  data["uses"].GetInt());
	}
	return;
}

std::unique_ptr<Condition> Configureader::getCondition(rapidjson::Value& v) {
	std::string type = v["type"].GetString();
	rapidjson::Value& p = v["params"];
	if (type == "DNE") {
		return std::make_unique<Condition>(p[0].GetInt(), COND::DNE, p[1].GetInt(), p[2].GetInt());
	}
	if (type == "EXISTS") {
		return std::make_unique<Condition>(p[0].GetInt(), COND::EXISTS, p[1].GetInt(), p[2].GetInt());
	}
	return nullptr;
}

void Configureader::ReadGlobalEvents(std::list<std::unique_ptr<GlobalEvent>>* globEvtArr, std::unordered_set<int>* evtSet) {
	if (dataDoc == nullptr) {
		initDataDoc();
	}
	rapidjson::Value& globalevts = (*dataDoc)["globalevents"];
	for (rapidjson::SizeType i = 0; i < globalevts.Size(); i++) {
		auto& data = globalevts[i];
		int floor = data["floor"].GetInt();
		if (floor > MAXFLOOR)
			continue;
		rapidjson::Value& events = data["events"];
		for (rapidjson::SizeType j = 0; j < events.Size(); j++) {
			auto& evtData = events[j];
			int id = evtData["id"].GetInt();
			if (evtSet&&evtSet->find(id) == evtSet->end())
				continue;
			std::unique_ptr<GlobalEvent> gEvt = std::make_unique<GlobalEvent>(id);
			rapidjson::Value& conditionData = evtData["conditions"];
			for (rapidjson::SizeType k = 0; k < conditionData.Size(); k++) {
				gEvt->addCondition(std::move(getCondition(conditionData[k])));
			}
			rapidjson::Value& actionsData = evtData["actions"];
			for (rapidjson::SizeType k = 0; k < actionsData.Size(); k++) {
				gEvt->attachAction(std::move(getAction(actionsData[k])));
			}
			globEvtArr[floor].push_back(std::move(gEvt));
		}
	}
}


std::string Configureader::GetStr(const std::string& tag) {
	if (langStrDoc == nullptr) {
		initLangDoc();
	}
	return ((*langStrDoc)["English"])[tag.c_str()].GetString();
}

std::string Configureader::GetDescription(const std::string& desc) {
	if (langStrDoc == nullptr) {
		initLangDoc();
	}
	return ((*langStrDoc)["English"])["description"][desc.c_str()].GetString();
}

void Configureader::GetDialog(const std::string& tag, std::vector<std::string>& strVec)
{
	if (langStrDoc == nullptr) {
		initLangDoc();
	}
	rapidjson::Value& dialogs = ((*langStrDoc)["English"])["dialog"][tag.c_str()];
	for (rapidjson::SizeType i = 0; i < dialogs.Size(); i++) {
		strVec.push_back(dialogs[i].GetString());
	}
}


void Configureader::initDataDoc() {
	dataDoc = std::make_unique<rapidjson::Document>();
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename("res/gamedata.json");
	auto strdata = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	dataDoc->Parse<0>(strdata.c_str());
}

void Configureader::initLangDoc()
{
	langStrDoc = std::make_unique<rapidjson::Document>();
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(curLanguageFile);
	auto strdata = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	langStrDoc->Parse<0>(strdata.c_str());
	//auto err=langStrDoc->GetParseError(); //for debugging
	//auto errPos=langStrDoc->GetErrorOffset();
}


Configureader::~Configureader() {
}