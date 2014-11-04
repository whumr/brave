#include "npc/Npc.h"

Npc::Npc(){}
Npc::~Npc(){}

void Npc::addAnimation()
{
	auto animationCache = AnimationCache::getInstance();
	// check if already loaded
	auto animation = animationCache->getAnimation(String::createWithFormat("%s-%s",_name.c_str(),_animationNames[0].c_str())->getCString());
	if(animation)
		return;	
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	for(int i=0; i<_animationNum; i++)
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		//put frames into animation
		for(int j = 0; j < _animationFrameNum[i] ; j++)
		{
			auto sfName = String::createWithFormat("%s-%d-%d.png",_name.c_str(), i+1, j+1)->getCString();
			auto sf = spriteFrameCache->getSpriteFrameByName(sfName);
			animation->addSpriteFrame(sf);
		}
		// put the animation into cache
		animationCache->addAnimation(animation, String::createWithFormat("%s-%s",_name.c_str(), 
					_animationNames[i].c_str())->getCString());
	}
}

Animate* Npc::getAnimateByType(AnimationType type)
{
	if(type <0 || type >= _animationNum)
	{
		CCLOG("illegal animation index!");
		return nullptr;
	}
	auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[type].c_str())->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(str);
	auto animate = Animate::create(animation);
	animate->setTag(type);
	return animate;
}

void Npc::playAnimationForever(AnimationType type)
{
	auto act = this->getActionByTag(type);
	if(act)
		return;
	if(type <0 || type >= _animationNum)
	{
		CCLOG("illegal animation index!");
		return;
	}
	for(int i=0;i<_animationNum;i++)
	{
		this->stopActionByTag(i);
	}	
	auto animate = this->getAnimateByType(type);
	auto animation = RepeatForever::create(animate);
	animation->setTag(type);
	this->runAction(animation);
}

void Npc::stop()
{
	this->stopAllActions();
	this->setSpriteFrame(_initFrame);
}

void Npc::walkTo(Vec2 dest)
{
	this->stopAllActions();
	auto move = MoveTo::create((dest - this->getPosition()).getLength() / _speed, dest);
	auto seq = Sequence::create(move, CallFunc::create([&]{this->stop();}), nullptr);
	this->playAnimationForever(WALKING);
	this->runAction(seq);
}

void Npc::idle(){}	

void Npc::attack()
{
	this->stopAllActions();
	this->playAnimationForever(ATTACKING);
}

void Npc::die(){}
bool Npc::onTouch(Touch* touch, Event* event){return true;}