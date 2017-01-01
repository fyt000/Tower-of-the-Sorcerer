#include "MyEvent.h"

class PostEvent: public MyEvent{

public:
	PostEvent(int imageIdx,const std::string& decription);
	PostEvent(int imageIdx,const std::string& decription,int imageIdx2);
	virtual PostEvent* clone();
	virtual ~PostEvent(); 

    virtual bool triggerEvent();
	virtual bool stepOnEvent();

};