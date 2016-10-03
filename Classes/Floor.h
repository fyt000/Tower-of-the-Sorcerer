#pragma once
class MyEvent;

class Floor
{
public:
	Floor();
	~Floor();

private:
	MyEvent* cells[11][11];
};

