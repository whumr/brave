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
	auto seq = Sequence::create(move, CallFunc::create([&]{this->checkTarget();}), NULL);
	this->playAnimationForever(WALKING);
	this->runAction(seq);
}

void Npc::idle(){}	

void Npc::attack()
{
	this->stopAllActions();
	auto animate = this->getAnimateByType(ATTACKING);
	auto attackCallback = CallFunc::create([&]{
		auto target = this->checkTarget();
		if (target)
			target->beAttacked(this);
		this->checkTarget();
	});
	auto attack = Sequence::create(animate, attackCallback, NULL);
	this->runAction(attack);
}

void Npc::addTarget(Npc* target)
{
	if (this->_targets.empty() || !this->_targets.contains(target))
		this->_targets.pushBack(target);
}

void Npc::removeTarget(Npc* target)
{
	if (!this->_targets.empty() && this->_targets.contains(target))
		this->_targets.eraseObject(target);
}

Npc* Npc::checkTarget()
{
	if (!this->_targets.empty())
	{
		Npc* target = this->_targets.front();
		if (target)
		{
			this->attack();
			return target;
		}
		else
			this->stop();
	}
	else
		this->stop();
	return NULL;
}

void Npc::beAttacked(Npc* empty)
{
	this->_hp = this->_hp - empty->_damage;
	if (this->_hp <= 0)
	{
		this->die();
		empty->removeTarget(this);
	}
}

void Npc::die()
{
	this->stopAllActions();
	auto die = this->getAnimateByType(DEAD);	
	if (this->_type != PLAYER)
	{
		auto blink = Blink::create(1.5, 3);
		auto callback = CallFunc::create([&]{
			this->stopAllActions();
			this->getParent()->removeChild(this);
		});
		this->runAction(Sequence::create(die, blink, callback, NULL));
	}
	else
		this->runAction(die);
}
bool Npc::onTouch(Touch* touch, Event* event){return true;}