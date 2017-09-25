#pragma once
#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include "Configureader.h"

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



enum class BLOCKTYPE : int {
	GLOBALBLOCK,
	FIGHT,
	SIZE
};

enum class DIR : int {
	UP, DOWN, LEFT, RIGHT
};

enum class DIALOGTYPE : int {
	NONE, YN, LIST, MATRIX
};

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int, int>> PATH;

template <typename T>
static std::string ToString(const T& val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}


//sprintf that works on std::string
//mostly taken from:
//http://www.stroustrup.com/C++11FAQ.html#variadic-templates
//replace %d %s etc.. with string, number... %% -> %
//thinking of just using @ as the placeholder
//no further formating (eg. %lf will not work)
static void stdsprintf(std::stringstream& ss, const char* s) {
	while (s && *s) {
		ss << *s++;
	}
}

template<typename T, typename... Args>
static void stdsprintf(std::stringstream& ss, const char* s, T value, Args... args) {
	while (s && *s) {
		if (*s == '%' && *++s != '%') {
			ss << value;
			return stdsprintf(ss, ++s, args...);
		}
		ss << *s++;
	}
}


template<typename... Args>
static std::string stdsprintf(const std::string& s, Args... args) {
	std::stringstream ss;
	stdsprintf(ss, &s[0], args...);
	return ss.str();
}


#define GStr( s ) Configureader::GetStr(s)