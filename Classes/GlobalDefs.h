#pragma once
#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include "Configureader.h"

//just defines nothing else
//I will run into forward decl issues if I put everything in gamedata (eg. Hero class)

enum DIR{
	UP,DOWN,LEFT,RIGHT
};

enum DIALOGTYPE{
	NONE,YN,SHOP
};

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int,int>> PATH;

template <typename T>
static std::string ToString(const T& val){
	std::stringstream ss;
	ss<<val;
	return ss.str();
}


//sprintf that works on std::string
//mostly taken from:
//http://www.stroustrup.com/C++11FAQ.html#variadic-templates
//replace %d %s etc.. with string, number... %% -> %
//thinking of just using @ as the placeholder
//no further formating (eg. %lf will not work)
template<typename... Args>
static std::string stdsprintf(std::string &s,Args... args){
	std::stringstream ss;
	stdsprintf(ss,&s[0],args...);
	return ss.str();
}


static void stdsprintf(std::stringstream& ss,const char* s){
	while (s && *s){
		ss << *s++;
	}
}

template<typename T,typename... Args>		
static void stdsprintf(std::stringstream& ss,const char* s,T value,Args... args){
	while (s && *s){
		if (*s=='%' && *++s!='%'){	
			ss << value;	
			return stdsprintf(ss,++s,args...);
		}
		ss << *s++;
	}
}


#define GStr( s ) Configureader::GetStr(s)