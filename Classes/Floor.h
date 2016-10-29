#pragma once
class MyEvent;

class Floor
{
public:
	Floor(int floorEvents[11*11]);
	~Floor();

private:
	MyEvent* cells[11][11];
	int tiles[11][11]; //this may change - but whatever
};

