#pragma once
#include "MyEvent.h"


enum KeyType{
	YELLOW,BLUE,RED,LAST
};


class Key:
	public MyEvent
{
public:
	Key(int imageIdx,std::string desc,enum KeyType keyType);
	bool triggerEvent();
	virtual ~Key();
	Key* clone();

private:
	enum KeyType keyType;

};
