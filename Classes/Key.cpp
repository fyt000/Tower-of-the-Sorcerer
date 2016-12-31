#include "Key.h"
#include "GameData.h"
#include "HeroX.h"
#include "LabelBinder.h"

Key::Key(int imageIdx,const std::string& desc,KeyType keyType):MyEvent(imageIdx,desc),keyType(keyType)
{
}

bool Key::triggerEvent(){
	GameData::getInstance()->hero->keys[keyType]->addVal(1);
	GameData::getInstance()->log(stdsprintf(GStr("get_key"),GStr("key_"+ToString((int)keyType)))); 
	return true;
}

Key::~Key()
{
}

Key * Key::clone()
{
	return new Key(*this);
}
