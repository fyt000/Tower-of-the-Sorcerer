#pragma once

#include "json/document.h"
#include "json/reader.h"
#include <vector>

class MyEvent;
class MyAction;
class HeroItem;

class Configureader{
	static rapidjson::Document* langStrDoc;

	

	~Configureader();

public:
	static bool ReadEventData(MyEvent**,int maxEvent);
	static bool ReadFloorEvents(int FloorArr[][11][11],int maxFloor,int maxx,int maxy);
	static bool ReadItemData(HeroItem**,int maxItem);
	static std::string GetStr(std::string tag);
	static std::string GetDescription(std::string& desc);
	static void GetDialog(std::string& tag,std::vector<std::string>& strVec);

private:
	static MyAction* getAction(rapidjson::Value&);
	static void initLangDoc();
	static std::string curLanguageFile;
};
