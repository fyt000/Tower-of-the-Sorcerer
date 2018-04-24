#include "MyEvent.h"


//difference from MyEvent is that performAction is called on stepOnEvent (eg. post triggerEvent)
//where MyEvent calls performAction before stepping on it

class PostEvent : public MyEvent {

public:
	PostEvent(int imageIdx, const std::string& decription);
	PostEvent(int imageIdx, const std::string& decription, int imageIdx2);
	virtual ~PostEvent();

	virtual bool triggerEvent();
	virtual bool stepOnEvent();

};