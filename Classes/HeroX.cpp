#include "HeroX.h"
#include "TransformCoordinate.h"
#include "GameData.h"
#include "FightableSnapshot.h"
#include "LabelBinder.h"

USING_NS_CC;

HeroX::HeroX(int imageIdx,std::string desc,int hp,int atk,int def,int gold):Fightable(imageIdx,desc,-1,hp,atk,def,gold){
	//hard coding these for now
	x=2;y=4;
	heroDir=DIR::UP;
	//these are fightable labels
	//this->setLabelNofity(true);
	//key labels
	for (int i=0;i<KeyType::LAST;i++){
		keys[i] = new LabelBinder<int>(3);
	}
}


bool HeroX::canAtk(){ //?
	return true;
}

bool HeroX::spendGold(int amt){
	if (gold.V()>=amt){
		gold.subVal(amt);
		return true;
	}
	return false;
}


Sprite* HeroX::getSprite(){
	
	if (sprite!=NULL){
		return sprite;
	}
	std::stringstream ss2;
	ss2<<"images/tile ("<<imageIdx<<").png";
	auto sprite2=Sprite::create(ss2.str());
	std::pair<int,int> pxy=TransformCoordinate::transform(x,y);
	sprite2->setPosition(pxy.first,pxy.second);
	sprite2->setScale(Director::getInstance()->getContentScaleFactor());
	sprite2->setAnchorPoint(Vec2(0,0));
	sprite=sprite2;
	return sprite2;
}

int HeroX::fightX(Fightable * target,std::function<void(Fightable&)> hpCallback1,std::function<void(Fightable&)> hpCallback2){
	//hpCallBack should really just be null... I don't care
	//this may change

	Director::getInstance()->getEventDispatcher()->setEnabled(false);
	target->setLabelNofity(false);
	this->setLabelNofity(false);
	std::vector<FightableSnapshot> heroSnapshots;
	std::vector<FightableSnapshot> enemySnapshots;
	//this allows calculation done in one method... without jumping around
	int ret=Fightable::fight(target,
		[&enemySnapshots](Fightable &f) {
			FightableSnapshot ss(f.getHp(),f.getAtk(),f.getDef());
			enemySnapshots.push_back(ss);
		},
		[&heroSnapshots](Fightable &f) { //capture heroSnapshots 
			FightableSnapshot ss(f.getHp(),f.getAtk(),f.getDef());
			heroSnapshots.push_back(ss);
		}
	);
	
	//simulate everything by callbacks...
	//because this is way too advanced for me

	std::string stepFrame1;
	std::string stepFrame2;
	switch (heroDir){
		case DIR::DOWN:stepFrame1="images/tile (189).png";stepFrame2="images/tile (191).png";break;
		case DIR::LEFT:stepFrame1="images/tile (197).png";stepFrame2="images/tile (199).png";break;
		case DIR::RIGHT:stepFrame1="images/tile (205).png";stepFrame2="images/tile (207).png";break;
		case DIR::UP:stepFrame1="images/tile (213).png";stepFrame2="images/tile (215).png";break;
		default:stepFrame1="images/tile (213).png";stepFrame2="images/tile (215).png";
	}
	log("has frames %d",heroSnapshots.size());
	Vector<FiniteTimeAction*> actions;
	int hSSIdx=0;
	int eSSIdx=0;
	target->setLabelNofity(true);
	this->setLabelNofity(true);
	for (int i=0;i<heroSnapshots.size()+enemySnapshots.size();i++){
		if (i%2==0){
			//enemy action		
			auto enemyCallback=CallFuncN::create(CC_CALLBACK_1(HeroX::updateBetweenFight,this,target,enemySnapshots,eSSIdx,stepFrame2,false));
			eSSIdx++;
			actions.pushBack(enemyCallback);
			actions.pushBack(DelayTime::create(0.3));
		}
		else{
			
			auto heroCallback=CallFuncN::create(CC_CALLBACK_1(HeroX::updateBetweenFight,this,this,heroSnapshots,hSSIdx,stepFrame1,true));
			hSSIdx++;
			actions.pushBack(heroCallback);
			actions.pushBack(DelayTime::create(0.3));
		}
	}
	actions.pushBack(CallFuncN::create(CC_CALLBACK_1(HeroX::StopAllFinal,this)));
	actions.pushBack(CallFuncN::create(CC_CALLBACK_1(HeroX::cleanUpTarget,this,target)));
	sprite->runAction(Sequence::create(actions));
	return ret;
}

void HeroX::cleanUpTarget(Node* node,Fightable * target){
	GameData::getInstance()->killEvent(std::pair<int,int>(target->getX(),target->getY()));
}

void HeroX::updateBetweenFight(Node* n,Fightable* f,std::vector<FightableSnapshot> &snapshots,int hSSIdx,std::string &frameName,bool isHero){
	auto gInst=GameData::getInstance();
	f->hp.setVal(snapshots[hSSIdx].hp);
	f->atk.setVal(snapshots[hSSIdx].atk);
	f->def.setVal(snapshots[hSSIdx].def);
	//f==this means its hero->..
	if (isHero&&hp.V()<=0){
		sprite->stopAllActions();
		gInst->gameover();
		return;
	}
	auto newFrame=SpriteFrame::create(frameName,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor()));
	sprite->setSpriteFrame(newFrame);
}

enum DIR nextNodeDir(std::pair<int,int> cur,std::pair<int,int> next){
	if (next.first-cur.first>0)
		return(DIR::DOWN);
	else if (next.first-cur.first<0)
		return(DIR::UP);
	else if (next.second-cur.second>0)
		return(DIR::RIGHT);
	else if (next.second-cur.second<0)
		return(DIR::LEFT);
	return DIR::UP;
}



Animate* HeroX::getDirMoveAnimate(enum DIR dir,int steps,bool stop){
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(steps+2);


	std::string stepFrame1;
	std::string stepFrame2;
	//hard coding the pngs
	switch (dir){
		case DIR::DOWN:stepFrame1="images/tile (185).png";stepFrame2="images/tile (187).png";break;
		case DIR::LEFT:stepFrame1="images/tile (193).png";stepFrame2="images/tile (195).png";break;
		case DIR::RIGHT:stepFrame1="images/tile (201).png";stepFrame2="images/tile (203).png";break;
		case DIR::UP:stepFrame1="images/tile (209).png";stepFrame2="images/tile (211).png";break;
		default:stepFrame1="images/tile (209).png";stepFrame2="images/tile (211).png";
	}

	for (int i=0;i<steps+1;i++){
		if (i%2==0)
			animFrames.pushBack(SpriteFrame::create(stepFrame1,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
		else
			animFrames.pushBack(SpriteFrame::create(stepFrame2,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor())));
	}
	if (stop){
		animFrames.pushBack(stopSprite(dir));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames,animateRate);
	Animate* animate = Animate::create(animation);
	animate->setTag(0); //all animations are 0
	return animate;
}


//this is used for arrow(keyboard) movement if I happen to implement it
//but again, this does not make any assumption on its surroundings
//just move
void HeroX::move(enum DIR direction){
	MoveTo* moveTo;
	int newX=x;int newY=y;
	switch (direction){
	case (DIR::UP):
		newX--;break;
	case(DIR::DOWN):
		newX++;break;
	case(DIR::LEFT):
		newY--;break;
	case(DIR::RIGHT):
		newY++;break;
	}

	move(std::pair<int,int>(newX,newY));
}

//THIS WORKS!!
//there are a lot of stuff that can happen with move
//for now, just do the animation
//and the logic for hitting the wall should be done else where maybe GameData
void HeroX::move(PATH path,bool isLastStep){
	sprite->stopAllActions();
	if (path.size()==0)
		return;

	/*
	if (isLastStep&&path.size()!=1)
		return;*/
	std::pair<int,int> lastStep = path.back();
	if (!isLastStep)
		path.pop_back();

	//break down the path into directions...
	//because each direction has a different animation
	std::vector< std::pair< PATH, enum DIR> > directedPaths;
	enum DIR curDir=heroDir;
	std::pair<int,int> curCoord(x,y); //do I need a lock on x,y or something
	PATH singleDirPath;
	for (int i=0;i<path.size();i++){
		enum DIR nextDir = nextNodeDir(curCoord,path[i]);
		if (nextDir!=curDir){ //change of direction
			if (singleDirPath.size()!=0)
				directedPaths.push_back( std::pair<PATH,enum DIR>(singleDirPath,curDir));
			curDir=nextDir;
			singleDirPath.clear();
		}
		curCoord=path[i];
		singleDirPath.push_back(curCoord);
	}
	if (singleDirPath.size()!=0)
		directedPaths.push_back(std::pair<PATH,enum DIR>(singleDirPath,curDir));


	
	//I could have combined this with the above code
	//but just in case I decide to do something different
	Vector<FiniteTimeAction*> actions;

	//now directedPaths stores all the stuff... 
	for (auto singPath:directedPaths){
		auto changeDirCallBack = CallFuncN::create(CC_CALLBACK_1(HeroX::changeDirAnimate,this,singPath.second,singPath.first.size(),false));
		actions.pushBack(changeDirCallBack);
		for (auto pathNode:singPath.first){
			auto destCoord=TransformCoordinate::transformVec2(pathNode.first,pathNode.second);
			auto callback = CallFuncN::create(CC_CALLBACK_1(HeroX::Destined,this,pathNode.first,pathNode.second));
			actions.pushBack(MoveTo::create(animateRate,destCoord));
			actions.pushBack(callback);
		}
	}
	if (isLastStep)
		actions.pushBack(DelayTime::create(animateRate));
	auto stopCallBack =
		isLastStep?CallFuncN::create(CC_CALLBACK_1(HeroX::StopAllFinal,this)):CallFuncN::create(CC_CALLBACK_1(HeroX::StopAll,this,lastStep));
	actions.pushBack(stopCallBack);
	
	if (isLastStep){
		// isLastStep is set to true when an event has triggered... Now trigger StepOn
		//this is probably not the right way to do it, but I don't know how aside from cascading it
		auto idk = GameData::getInstance()->getEvent(lastStep.first,lastStep.second);
		if (idk){
			auto stepOnCallBack = CallFuncN::create(CC_CALLBACK_1(HeroX::triggeredCallback,this,idk));
			actions.pushBack(stepOnCallBack);
		}
		
	}


	auto seq = Sequence::create(actions);
	sprite->runAction(seq);
}

void HeroX::move(std::pair<int,int> dest)
{
	PATH p;
	p.push_back(dest);
	move(p,true);
}

void HeroX::changeDirAnimate(Node* node,enum DIR newDir,int steps,bool stop){
	heroDir=newDir;
	auto animate=getDirMoveAnimate(newDir,steps,stop);
	sprite->stopActionByTag(0); //stop cur animation if any
	sprite->runAction(animate);
}

void HeroX::Destined(Node* node,int x,int y){
	this->x=x;this->y=y;
}

void HeroX::StopAll(Node* node,std::pair<int,int> dest){
	Director::getInstance()->getEventDispatcher()->setEnabled(false);
	//sprite->stopAllActions();
	sprite->setSpriteFrame(stopSprite(heroDir));
	GameData::getInstance()->moveHeroFinalStep(dest);
}

//theres a few lines of copied code... get ride of it maybe
void HeroX::StopAllFinal(Node * node)
{
	sprite->stopAllActions();
	sprite->setSpriteFrame(stopSprite(heroDir));
	GameData::getInstance()->showLog();
	Director::getInstance()->getEventDispatcher()->setEnabled(true);
}

SpriteFrame* HeroX::stopSprite(DIR dir){
	std::string stopStr;
	switch (dir){
	case DIR::DOWN:stopStr="images/tile (189).png";break;
	case DIR::LEFT:stopStr="images/tile (197).png";break;
	case DIR::RIGHT:stopStr="images/tile (205).png";break;
	case DIR::UP:stopStr="images/tile (213).png";break;
	default:stopStr="images/tile (213).png";
	}
	return SpriteFrame::create(stopStr,Rect(0,0,40/Director::getInstance()->getContentScaleFactor(),40/Director::getInstance()->getContentScaleFactor()));
}

void HeroX::triggeredCallback(Node * node,MyEvent* ev){
	if (ev==nullptr)
		return;
	if (!ev->stepOnEvent()){
		Director::getInstance()->getEventDispatcher()->setEnabled(true);
	}
}

HeroX::~HeroX(){
	for (int i=0;i<KeyType::LAST;i++)
		delete keys[i];
}

void HeroX::changeFacingDir(std::pair<int,int> dest)
{
	HeroX::changeDirAnimate(NULL,nextNodeDir(std::pair<int,int>(x,y),dest),1,true);
}

void HeroX::setAbsPos(int absx,int absy,enum DIR dir)
{
	setXY(absx,absy);
	std::pair<int,int> pxy=TransformCoordinate::transform(absx,absy);
	sprite->setPosition(pxy.first,pxy.second);
	heroDir=dir;
	changeFacingDir(dir);
}

void HeroX::changeFacingDir(enum DIR dir)
{
	HeroX::changeDirAnimate(NULL,dir,1,true);
}


HeroX * HeroX::clone()
{
	return new HeroX(*this);
}
