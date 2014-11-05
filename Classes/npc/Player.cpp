#include "npc/Player.h"

Player::Player(){}
Player::~Player(){}

bool Player::init()
{
	_initFrame = "player1-1-1.png";
	_name = "player1";
	_type = NpcType::PLAYER;
	_speed = 100;
	_hp = 100;
	_maxHp =100;
	_damage = 20;

	_animationNum = 5;
	int animationFrameNum[5] ={4, 4, 4, 2, 4};
	_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);

	std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
	_animationNames.assign(animationNames, animationNames + 5);

	this->initWithSpriteFrameName(_initFrame);
	//load animation
	this->addAnimation();

	//set contact
	auto body = PhysicsBody::createBox(Size(120, 30), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(-40, 10));
	body->setCategoryBitmask(ColliderType::ColliderTypePlayer);
	body->setCollisionBitmask(ColliderType::ColliderTypeNone);
	body->setContactTestBitmask(ColliderType::ColliderTypeMonster | ColliderType::ColliderTypeBOSS);
	this->setPhysicsBody(body); 

//	_listener = EventListenerTouchOneByOne::create();
//	_listener->setSwallowTouches(true);
//	_listener->onTouchBegan = CC_CALLBACK_2(Player::onTouch,this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,this);
	return true;
}

bool Player::onTouch(Touch* touch, Event* event)
{
	return true;
}

//void Player::attack()
//{
//	this->stopAllActions();
//	this->playAnimationForever(ATTACKING);
//
//	Npc* target = this->_targets.front();
//	if (target)
//		target->beAttacked(this);
//}