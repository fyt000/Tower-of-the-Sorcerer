#include "Fightable.h"
USING_NS_CC;

Fightable::Fightable(int id,std::string desc,int hp,int atk,int def):MyEvent(id,desc),hp(hp),atk(atk),def(def){}


Fightable::~Fightable(){
}
