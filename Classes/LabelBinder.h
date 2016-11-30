#pragma once
#include "cocos2d.h"
#include "GlobalDefs.h"



//kinda of observer pattern, not exactly
template <class T>
class LabelBinder{
public:
	LabelBinder(T);

	LabelBinder(T,cocos2d::Label* label);

	void attach(cocos2d::Label* label);
	void setVal(T newVal);
	void addVal(T v);
	void subVal(T v);
	void notify();
	void setNofify(bool);
	T V();

private:
	cocos2d::Label* theLabel;
	bool doNotify=true;
	T value;
};