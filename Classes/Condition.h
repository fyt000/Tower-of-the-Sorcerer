#pragma once

enum COND {
	EXISTS,
	DNE, // does not exists
	AT	 // check if hero is currently at this location
};

//extend this class for more conditions...
//only check for existence
class Condition {
public:
	Condition(int floor, COND cond, int x, int y);
	virtual bool check();
	virtual ~Condition();
protected:
	int floor;
	enum COND cond;
	int x;
	int y;
};