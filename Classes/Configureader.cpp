#include "Configureader.h"
#include "json/document.h"
#include "json/reader.h"
#include "cocos2d.h"
#include "Wall.h"
#include "Enemy.h"
#include "Consumable.h"
#include "Door.h"
#include "Key.h"

bool Configureader::ReadEventData(MyEvent ** EventArr,int maxEvent)
{
	rapidjson::Document edJSON;
	//comment not supported in the bundled version of rapidjson
	//TODO use proper buffering or filestream
	edJSON.Parse(cocos2d::FileUtils::getInstance()->getStringFromFile("res/gamedata.json").c_str());
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
	feJSON.Parse(cocos2d::FileUtils::getInstance()->getStringFromFile("res/gamedata.json").c_str());
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
