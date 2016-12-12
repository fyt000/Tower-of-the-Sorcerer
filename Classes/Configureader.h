#pragma once

#include "json/document.h"
#include "json/reader.h"



class MyEvent;

class Configureader{
	static rapidjson::Document* langStrDoc;

	~Configureader();

public:
	static bool ReadEventData(MyEvent**,int maxEvent);
	static bool ReadFloorEvents(int FloorArr[][11][11],int maxFloor,int maxx,int maxy);
	static std::string GetStr(std::string tag);
	static std::string GetDescription(std::string desc);

private:
	static void initLangDoc();
	static std::string curLanguageFile;
};
