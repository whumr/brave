#include "npc/Monster.h"

Monster::Monster(){}
Monster::~Monster(){}

Monster* Monster::create(NpcType type)
{
	Monster* monster = new Monster();
	monster->setType(type);
	if(monster && monster->init())
	{
		monster->autorelease();
		return monster;
	}
	else
	{
		delete monster;
		monster = NULL;
		return NULL;
	}
}

bool Monster::init()
{
	std::string sfName = "";
	switch (_type)
	{
	case NpcType::MONSTER1:
		sfName = "enemy1-1-1.png";
		_name = "enemy1";
		break;
	case NpcType::MONSTER2:
		sfName = "enemy2-1-1.png";
		_name = "enemy2";
		break;
	default:
		return false;
	}
	_speed = 80;
	_hp = 100;
	_maxHp =100;
	_damage = 20;

	_animationNum = 5;
	int animationFrameNum[5] ={3, 3, 3, 2, 0};
	_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);

	std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
	_animationNames.assign(animationNames, animationNames + 5);

	this->initWithSpriteFrameName(sfName);
	//load animation
	this->addAnimation();

	//set contact
	auto body = PhysicsBody::createBox(Size(120, 30), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(40, 0));
	//auto size = this->getContentSize();
	//CCLOG("monster size: %f, %f ",size.width, size.height);
	//body->addShape(PhysicsShapeBox::create(size));
	body->setCategoryBitmask(ColliderType::ColliderTypeMonster);
	body->setCollisionBitmask(ColliderType::ColliderTypeNone);
	body->setContactTestBitmask(ColliderType::ColliderTypePlayer);
	this->setPhysicsBody(body); 

//	_listener = EventListenerTouchOneByOne::create();
//	_listener->setSwallowTouches(true);
//	_listener->onTouchBegan = CC_CALLBACK_2(Monster::onTouch,this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,this);
	return true;
}

bool Monster::onTouch(Touch* touch, Event* event)
{
	return true;
}