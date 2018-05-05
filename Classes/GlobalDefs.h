#pragma once
#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include "Configureader.h"

#define GStr( s ) Configureader::GetStr(s)

namespace twsutil {

//just defines nothing else
//I will run into forward decl issues if I put everything in gamedata (eg. Hero class)

//hard max... for array size and to simplify the code
//its possible to set it higher
const int MAXFLOOR = 51;
const int MAXITEMS = 9;

//no reason to hard code these limits
//but anyway...
const int MAXEVENT = 500;
//const int MAXGLOBAL=10; //per floor

enum class DIR : int {
	UP, DOWN, LEFT, RIGHT, NONE
};

enum class DIALOGTYPE : int {
	NONE, YN, LIST, MATRIX
};

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int, int>> PATH;

//sprintf that works on std::string
//mostly taken from:
//http://www.stroustrup.com/C++11FAQ.html#variadic-templates
//replace %d %s etc.. with string, number... %% -> %
//thinking of just using @ as the placeholder
//no further formating (eg. %lf will not work)
void static stdsprintf(std::stringstream& ss, const char* s) {
	while (s && *s) {
		ss << *s++;
	}
}

template<typename T, typename... Args>
void static stdsprintf(std::stringstream& ss, const char* s, T value, Args... args) {
	while (s && *s) {
		if (*s == '%' && *++s != '%') {
			ss << value;
			return stdsprintf(ss, ++s, args...);
		}
		ss << *s++;
	}
}

template<typename... Args>
std::string static stdsprintf(const std::string& s, Args... args) {
	std::stringstream ss;
	stdsprintf(ss, &s[0], args...);
	return ss.str();
}
}