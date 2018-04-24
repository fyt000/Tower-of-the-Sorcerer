#include "PostEvent.h"
#include "GameData.h"
#include "GlobalDefs.h"

PostEvent::PostEvent(int imageIdx, const std::string& desc) :
	MyEvent(imageIdx, desc) {
}

PostEvent::PostEvent(int imageIdx, const std::string& desc, int imageIdx2) :
	MyEvent(imageIdx, desc, imageIdx2) {
}

bool PostEvent::triggerEvent() {
	return true;
}

bool PostEvent::stepOnEvent() {
	performActions();
	selfDestruct();
	return false;
}


PostEvent::~PostEvent()
{
}
