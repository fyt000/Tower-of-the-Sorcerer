#pragma once
#pragma once
#include <utility>
#include <vector>
#include <sstream>
#include <string>

//just defines nothing else
//I will run into forward decl issues if I put everything in gamedata (eg. Hero class)

enum DIR{
	UP,DOWN,LEFT,RIGHT
};

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int,int>> PATH;

template <typename T>
std::string ToString(const T& val){
	std::stringstream ss;
	ss<<val;
	return ss.str();
}