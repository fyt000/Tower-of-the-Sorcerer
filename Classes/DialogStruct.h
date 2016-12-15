#pragma once
#include <string>
#include <GlobalDefs.h>
#include <vector>

struct DialogStruct{
	std::string text;
	enum DIALOGTYPE dialogType;
	std::vector<std::string> options;
	DialogStruct(std::string s,enum DIALOGTYPE dtype):
		text(s),dialogType(dtype){}
	DialogStruct(std::string s,enum DIALOGTYPE dtype,std::vector<std::string> options):
		text(s),dialogType(dtype),options(options){}
};