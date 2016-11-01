#pragma once
#pragma once
#include <utility>
#include <vector>

//just defines nothing else

enum DIR{
	UP,DOWN,LEFT,RIGHT
};

//this is getting ugly... just going to typedef this
typedef std::vector<std::pair<int,int>> PATH;