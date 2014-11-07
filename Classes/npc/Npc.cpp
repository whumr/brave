#include "npc/Npc.h"
#include "util/RectUtil.h"

Npc::Npc(){}
Npc::~Npc(){}

void Npc::showProgress()
{
	if (_type == PLAYER)
	{
		_progress = Progress::create("player-progress-bg.png","player-progress-fill.png");
		_progress->setPosition(RectUtil::left().x + _progress->getContentSize().width/2, RectUtil::top().y - _progress->getContentSize().height/2);
		this->getParent()->addChild(_progress);
	}
	else
	{
		_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
		_progress->setPosition(150 , 200);
		this->addChild(_progress);
	}	
}

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

	auto left_bottom = RectUtil::leftBottom();
	auto right_top = RectUtil::rightTop();
	float min_x = left_bottom.x, min_y = left_bottom.y,
		max_x = right_top.x, max_y = right_top.y,
		x = dest.x, y = dest.y;
	if (x < min_x)
		x = min_x;
	else if (x > max_x)
		x = max_x;
	if (y < min_y)
		y = min_y;
	else if (y > max_y)
		y = max_y;

	dest = Vec2(x,y);
	auto position = this->getPosition();
	auto move = MoveTo::create(dest.getDistance(position) / _speed, dest);
	auto seq = Sequence::create(move, CallFunc::create([&]{
		auto target = this->getTarget();
		if (target)
			target->beAttacked(this);
		this->checkTarget();
	}), NULL);
	if (position.x >= dest.x && dest.x != max_x)
		this->setFlippedX(_type == PLAYER);
	else
		this->setFlippedX(_type != PLAYER);
	this->playAnimationForever(WALKING);
	this->runAction(seq);
}

void Npc::idle(){}	

void Npc::attack()
{
	auto animate = this->getAnimateByType(ATTACKING);
	auto attackCheck = CallFunc::create([&]{
		auto target = this->getTarget();
		if (!target)
			this->stop();
	});
	auto attackCallback = CallFunc::create([&]{
		auto target = this->getTarget();
		if (target)
			target->beAttacked(this);
		this->checkTarget();
	});
	auto attack = Sequence::create(DelayTime::create(this->getAttackDelay()), animate, attackCallback, NULL);
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

void Npc::checkTarget()
{
	this->stop();
	auto target = this->getTarget();
	if (target)
	{
		auto c_p = this->getPosition();
		auto t_p = target->getPosition();
		if (c_p.x > t_p.x)
			this->setFlippedX(_type == PLAYER);
		else
			this->setFlippedX(_type != PLAYER);	
		this->attack();
	}
}

Npc* Npc::getTarget()
{
	if (!this->_targets.empty())
	{
		Npc* target = this->_targets.front();
		if (target)
			return target;
	}
	return NULL;
}

void Npc::beAttacked(Npc* empty)
{
	this->_hp = this->_hp - empty->_damage;
	if (this->_hp <= 0)
	{
		this->_progress->setProgress(0);
		this->die();
		empty->removeTarget(this);
	}
	else
	{
		this->_progress->setProgress((float)_hp/_maxHp*100);
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
			this->setVisible(false);
			//this->getParent()->removeChild(this, false);
		});
		this->runAction(Sequence::create(die, blink, callback, NULL));
	}
	else
		this->runAction(die);
}
bool Npc::onTouch(Touch* touch, Event* event){return true;}