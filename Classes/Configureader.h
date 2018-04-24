#pragma once

#include "json/document.h"
#include "json/reader.h"
#include <vector>
#include <list>
#include <memory>
#include <unordered_map>

class MyEvent;
class MyAction;
class HeroItem;
class GlobalEvent;
class Condition;

class Configureader {

	~Configureader();

public:
	static std::unique_ptr<MyEvent> getEvent(int id);
	static void ReadFloorEvents(int FloorArr[][11][11]);
	static void ReadItemData(std::unique_ptr<HeroItem>*);
	static void ReadGlobalEvents(std::list<std::unique_ptr<GlobalEvent>>*);
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
	static std::unique_ptr<Condition> getCondition(rapidjson::Value&);
	static std::unique_ptr<MyAction> getAction(rapidjson::Value&);
	static void initLangDoc();
	static void initDataDoc();
	static std::string curLanguageFile;
	static std::unique_ptr<rapidjson::Document> langStrDoc;
	static std::unique_ptr<rapidjson::Document> dataDoc;
	static std::unordered_map<int, int> eventIdxMapping;
};
