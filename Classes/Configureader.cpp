#include "Configureader.h"
#include "MyEvent.h"
#include "cocos2d.h"
#include "Wall.h"
#include "Enemy.h"
#include "Consumable.h"
#include "Door.h"
#include "Key.h"
#include "Stairs.h"

rapidjson::Document* Configureader::langStrDoc=nullptr;

std::string Configureader::curLanguageFile="res/res_english.json";

bool Configureader::ReadEventData(MyEvent ** EventArr,int maxEvent)
{
	rapidjson::Document edJSON;
	//comment not supported in the bundled version of rapidjson
	//TODO use proper buffering or filestream
	//using fullPathForFilename made this work for reasons I do not understand
	//might be some other settings I've changed but I don't know
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename("res/gamedata.json");
	edJSON.Parse(cocos2d::FileUtils::getInstance()->getStringFromFile(path).c_str());
	auto err=edJSON.GetParseError();
	auto errPos=edJSON.GetErrorOffset();
	rapidjson::Value& eventdata = edJSON["eventdata"];
	/*
	for (auto evt=eventdata.MemberBegin();evt!=eventdata.MemberEnd();evt++){
	std::string idx=evt->name.GetString();
	std::string type=evt->value["type"].GetString();
	}*/
	for (rapidjson::SizeType i=0;i<eventdata.Size();i++){
		int idx=eventdata[i]["id"].GetInt();
		std::string type=eventdata[i]["type"].GetString();
		rapidjson::Value& p=eventdata[i]["params"];
		if (idx>=maxEvent)
			continue;
		delete EventArr[idx];
		if (type=="Door"){
			EventArr[idx]=new Door(p[0].GetInt(),p[1].GetString(),static_cast<KeyType>(p[2].GetInt()));
		}
		else if (type=="Wall"){
			EventArr[idx]=new Wall(p[0].GetInt(),p[1].GetString());
		}
		else if (type=="MyEvent"){
			EventArr[idx]=new MyEvent(p[0].GetInt(),p[1].GetString());
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
		/*
		else if (type==""){

		}
		else if (type==""){

		}
		*/
	}

	return true;
}

bool Configureader::ReadFloorEvents(int FloorArr[][11][11],int maxFloor,int maxx,int maxy)
{
	rapidjson::Document feJSON;
	//comment not supported in the bundled version of rapidjson
	//TODO use proper buffering or filestream
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename("res/gamedata.json");
	feJSON.Parse(cocos2d::FileUtils::getInstance()->getStringFromFile(path).c_str());
	auto err=feJSON.GetParseError();
	auto errPos=feJSON.GetErrorOffset();
	rapidjson::Value& floorevent = feJSON["floorevents"];
	
	for (rapidjson::SizeType i=0;i<floorevent.Size();i++){
		int idx=floorevent[i]["floor"].GetInt();
		if (idx>=maxFloor)
			continue;
		for (int x=0;x<maxx;x++){
			for (int y=0;y<maxy;y++){
				FloorArr[idx][x][y]=floorevent[i]["data"][x][y].GetInt();
			}
		}
	}
	return true;
}

std::string Configureader::GetStr(std::string tag){
	if (langStrDoc==nullptr){
		initLangDoc();
	}
	return ((*langStrDoc)["English"])[tag.c_str()].GetString();
}

std::string Configureader::GetDescription(std::string desc){
	if (langStrDoc==nullptr){
		initLangDoc();
	}
	return ((*langStrDoc)["English"])["description"][desc.c_str()].GetString();
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
}