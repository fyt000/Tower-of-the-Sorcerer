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

rapidjson::Document* Configureader::langStrDoc=nullptr;
rapidjson::Document* Configureader::dataDoc=nullptr;
std::string Configureader::curLanguageFile="res/res_english.json";

void Configureader::ReadEventData(MyEvent ** EventArr)
{
	int maxEvent=MAXEVENT;

	if (dataDoc==nullptr){
		initDataDoc();
	}

	rapidjson::Value& eventdata = (*dataDoc)["eventdata"];
	/*
	for (auto evt=eventdata.MemberBegin();evt!=eventdata.MemberEnd();evt++){
	std::string idx=evt->name.GetString();
	std::string type=evt->value["type"].GetString();
	}*/
	for (rapidjson::SizeType i=0;i<eventdata.Size();i++){
		auto& data = eventdata[i];
		int idx=data["id"].GetInt();
		std::string type=data["type"].GetString();
		rapidjson::Value& p=data["params"];
		if (idx>=maxEvent)
			continue;
		delete EventArr[idx];
		EventArr[idx]=NULL;
		if (type=="Door"){
			EventArr[idx]=new Door(p[0].GetInt(),p[1].GetString(),static_cast<KeyType>(p[2].GetInt()));
		}
		else if (type=="Wall"){
			EventArr[idx]=new Wall(p[0].GetInt(),p[1].GetString());
		}
		else if (type=="MyEvent"){
			if (p.Size()==2)
				EventArr[idx]=new MyEvent(p[0].GetInt(),p[1].GetString());
			else 
				EventArr[idx]=new MyEvent(p[0].GetInt(),p[1].GetString(),p[2].GetInt());
		}
		else if (type=="Key"){
			EventArr[idx]=new Key(p[0].GetInt(),p[1].GetString(),static_cast<KeyType>(p[2].GetInt()));
		}
		else if (type=="Consumable"){
			EventArr[idx]=new Consumable(p[0].GetInt(),p[1].GetString(),p[2].GetInt(),p[3].GetInt(),p[4].GetInt(),p[5].GetInt());
		}
		else if (type=="Enemy"){
			EventArr[idx]=new Enemy(p[0].GetInt(),p[1].GetString(),p[2].GetInt(),p[3].GetInt(),p[4].GetInt(),p[5].GetInt(),p[6].GetInt());
		}
		else if (type=="Stairs"){
			EventArr[idx]=new Stairs(p[0].GetInt(),p[1].GetString(),p[2].GetInt(),p[3].GetInt(),p[4].GetInt(),static_cast<DIR>(p[5].GetInt()));
		}
		else if (type=="Shop"){
			EventArr[idx]=new Shop(p[0].GetInt(),p[1].GetString(),p[2].GetInt(),p[3].GetInt(),p[4].GetInt(),p[5].GetInt());
		}
		else if (type=="PostEvent"){
			if (p.Size()==2)
				EventArr[idx]=new PostEvent(p[0].GetInt(),p[1].GetString());
			else 
				EventArr[idx]=new PostEvent(p[0].GetInt(),p[1].GetString(),p[2].GetInt());
		}

		/*
		else if (type==""){

		}
		else if (type==""){

		}
		*/
		auto actions = data.FindMember("actions");
		if (actions!= data.MemberEnd()){
			rapidjson::Value& actionsData = actions->value;
			for (rapidjson::SizeType j=0;j<actionsData.Size();j++){
				EventArr[idx]->attachAction(getAction(actionsData[j]));
			}
		}
	}
	return;
}


MyAction * Configureader::getAction(rapidjson::Value &data)
{
	MyAction* action=nullptr;
	MyAction* next=nullptr;
	auto nextData = data.FindMember("next");
	if (nextData!=data.MemberEnd()){
		next = getAction(nextData->value);
	}
	std::string type=data["action"].GetString();
	if (type=="Talk"){
		action = new Talk(next,data["tag"].GetString());
	}
	else if (type=="TalkYN"){
		action = new TalkYN(next,data["tag"].GetString());
	}
	else if (type=="TransformSelf"){
		action = new TransformSelf(next,data["new"].GetInt());
	}
	else if (type=="Obtain"){
		action = new Obtain(next,data["id"].GetInt());
	}
	else if (type=="LogText"){
		action = new LogText(next,data["tag"].GetString());
	}
	else if (type=="Transform"){
		action = new Transform(next,data["floor"].GetInt(),data["x"].GetInt(),data["y"].GetInt(),data["id"].GetInt());
	}
	else if (type=="FlatStat"){
		action = new FlatStat(next,GStr(data["description"].GetString()),data["hp"].GetInt(),data["atk"].GetInt(),data["def"].GetInt(),data["gold"].GetInt());
	}
	else if (type=="DestructSelf"){
		action = new DestructSelf(next);
	}
	return action;
}


void Configureader::ReadFloorEvents(int FloorArr[][11][11])
{
	int maxFloor=MAXFLOOR;
	int maxx=11;
	int maxy=11;
	if (dataDoc==nullptr){
		initDataDoc();
	}
	rapidjson::Value& floorevent = (*dataDoc)["floorevents"];
	
	for (rapidjson::SizeType i=0;i<floorevent.Size();i++){
		int idx=floorevent[i]["floor"].GetInt();
		if (idx>maxFloor)
			continue;
		for (int x=0;x<maxx;x++){
			for (int y=0;y<maxy;y++){
				FloorArr[idx][x][y]=floorevent[i]["data"][x][y].GetInt();
			}
		}
	}
	return;
}

void Configureader::ReadItemData(HeroItem **itemArr)
{
	int maxItem=MAXITEMS;
	if (dataDoc==nullptr){
		initDataDoc();
	}
	rapidjson::Value& itemdata = (*dataDoc)["items"];
	for (rapidjson::SizeType i=0;i<itemdata.Size();i++){
		auto& data = itemdata[i];
		int idx=data["id"].GetInt();
		if (idx>=maxItem)
			continue;
		itemArr[idx] = new HeroItem(idx,data["name"].GetString(),data["image"].GetInt(),
			HeroItem::getEffectFunction(data["effect"].GetString()),data["uses"].GetInt());
	}
	return;
}

Condition* Configureader::getCondition(rapidjson::Value& v){
	std::string type=v["type"].GetString();
	rapidjson::Value& p=v["params"];
	if (type=="DNE"){
		return new Condition(p[0].GetInt(),COND::DNE,p[1].GetInt(),p[2].GetInt());
	}
	if (type=="EXISTS"){
		return new Condition(p[0].GetInt(),COND::EXISTS,p[1].GetInt(),p[2].GetInt());
	}
	return nullptr;
}

 void Configureader::ReadGlobalEvents(std::list<GlobalEvent* >* globEvtArr){
	if (dataDoc==nullptr){
		initDataDoc();
	}
	rapidjson::Value& globalevts = (*dataDoc)["globalevents"];
	for (rapidjson::SizeType i=0;i<globalevts.Size();i++){
		auto& data = globalevts[i];
		int floor=data["floor"].GetInt();
		if (floor>MAXFLOOR)
			continue;
		rapidjson::Value& events = data["events"];
		for (rapidjson::SizeType j=0;j<events.Size();j++){
			auto& evtData = events[j];
			GlobalEvent* gEvt= new GlobalEvent();
			rapidjson::Value& conditionData = evtData["conditions"];
			for (rapidjson::SizeType k=0;k<conditionData.Size();k++){
				gEvt->addCondition(getCondition(conditionData[k]));
			}			
			rapidjson::Value& actionsData = evtData["actions"];
			for (rapidjson::SizeType k=0;k<actionsData.Size();k++){
				gEvt->attachAction(getAction(actionsData[k]));
			}
			globEvtArr[floor].push_back(gEvt);
		}
	}
 }


std::string Configureader::GetStr(std::string tag){
	if (langStrDoc==nullptr){
		initLangDoc();
	}
	return ((*langStrDoc)["English"])[tag.c_str()].GetString();
}

std::string Configureader::GetDescription(std::string& desc){
	if (langStrDoc==nullptr){
		initLangDoc();
	}
	return ((*langStrDoc)["English"])["description"][desc.c_str()].GetString();
}

void Configureader::GetDialog(std::string& tag,std::vector<std::string>& strVec)
{
	if (langStrDoc==nullptr){
		initLangDoc();
	}
	rapidjson::Value& dialogs=((*langStrDoc)["English"])["dialog"][tag.c_str()];
	for (rapidjson::SizeType i=0;i<dialogs.Size();i++){
		strVec.push_back(dialogs[i].GetString());
	}
}


void Configureader::initDataDoc(){
	dataDoc = new rapidjson::Document();
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename("res/gamedata.json");
	auto strdata=cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	dataDoc->Parse<0>(strdata.c_str());
}

void Configureader::initLangDoc()
{
	langStrDoc = new rapidjson::Document();
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(curLanguageFile);
	auto strdata=cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	langStrDoc->Parse<0>(strdata.c_str());
	auto err=langStrDoc->GetParseError(); //for debugging
	auto errPos=langStrDoc->GetErrorOffset();
}


Configureader::~Configureader(){
	delete langStrDoc;
	delete dataDoc;
}