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

class Configureader {
	static rapidjson::Document* langStrDoc;
	static rapidjson::Document* dataDoc;
	~Configureader();

public:
	static void ReadEventData(MyEvent**);
	static void ReadFloorEvents(int FloorArr[][11][11]);
	static void ReadItemData(HeroItem**);
	static void ReadGlobalEvents(std::list<GlobalEvent* >*);
	static std::string GetStr(const std::string& tag);
	static std::string GetDescription(const std::string& desc);
	static void GetDialog(const std::string& tag, std::vector<std::string>& strVec);

	// uhm, unclear what my intentions were but keep them here for now
	//void saveInt(const std::string&, int);
	//void saveInts(const std::string, std::vector<int>);
	//void saveFloorEvents(int FloorArr[][11][11]);

	//int readInt(const std::string&);
	//std::vector<int> readInts(const std::string&);

private:
	static Condition* getCondition(rapidjson::Value&);
	static MyAction* getAction(rapidjson::Value&);
	static void initLangDoc();
	static void initDataDoc();
	static std::string curLanguageFile;
};
