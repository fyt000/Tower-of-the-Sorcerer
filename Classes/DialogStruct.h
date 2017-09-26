#pragma once
#include <string>
#include "GlobalDefs.h"
#include <vector>

struct DialogStruct {
	std::string text;
	twsutil::DIALOGTYPE dialogType;
	//not many will have options
	std::vector<std::string> options;
	DialogStruct(const std::string& s, twsutil::DIALOGTYPE dtype) :
		text(s), dialogType(dtype) {}
	DialogStruct(const std::string& s, twsutil::DIALOGTYPE dtype, std::vector<std::string> options) :
		text(s), dialogType(dtype), options(options) {}
};