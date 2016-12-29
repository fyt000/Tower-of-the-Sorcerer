#pragma once

#include "json/document.h"
#include "json/reader.h"
#include <vector>
#include <list>

class MyEvent;
class MyAction;
class HeroItem;
class GlobalEvent;
class Condition;

class Configureader{
	static rapidjson::Document* langStrDoc;
	static rapidjson::Document* dataDoc;
	~Configureader();

public:
	static void ReadEventData(MyEvent**);
	static void ReadFloorEvents(int FloorArr[][11][11]);
	static void ReadItemData(HeroItem**);
	static void ReadGlobalEvents(std::list<GlobalEvent* >*);
	static std::string GetStr(std::string tag);
	static std::string GetDescription(std::string& desc);
	static void GetDialog(std::string& tag,std::vector<std::string>& strVec);

private:
	static Condition* getCondition(rapidjson::Value&);
	static MyAction* getAction(rapidjson::Value&);
	static void initLangDoc();
	static void initDataDoc();
	static std::string curLanguageFile;
};
