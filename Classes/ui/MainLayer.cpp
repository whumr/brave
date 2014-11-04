#include "ui/MainLayer.h"
#include "MainScene.h"
#include "util/RectUtil.h"
#include "util/MenuUtil.h"
#include "npc/Npc.h"
#include "npc/Boss.h"

bool MainLayer::init()
{
	if(!Layer::init())
		return false;
	this->addRoles();
	this->addUI();
	this->addListener();
	this->scheduleUpdate();
	return true;
}

bool MainLayer::onTouchBegan(Touch* touch, Event* event)
{
	CCLOG("MainLayer::onTouchBegan");
	Vec2 pos = this->convertToNodeSpace(touch->getLocation());
	if(_player)
		_player->walkTo(pos);
	return true;
}

void MainLayer::onTouchPause(Ref* sender)
{
	CCLOG("MainLayer::onTouchPause");
	auto main = (MainScene*)this->getParent();
	main->onTouchPause(sender);
}

void MainLayer::toggleDebug(Ref* pSender)
{
	CCLOG("MainLayer::toggleDebug");
	if(_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
		_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	else
		_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

void MainLayer::addRoles()
{
	//add player
	_player = Player::create();
	_player->setPosition(RectUtil::left().x + _player->getContentSize().width/2, RectUtil::top().y/2);
	this->addChild(_player);
	
	_monster = Monster::create(Monster::NpcType::MONSTER1);
	_monster->setPosition(RectUtil::center().x - _monster->getContentSize().width/2, RectUtil::center().y/2);
	this->addChild(_monster);

	auto boss = Boss::create();
	boss->setPosition(RectUtil::center().x - boss->getContentSize().width, RectUtil::center().y/2);
	this->addChild(boss);
}

void MainLayer::addUI()
{
	_progress = Progress::create("player-progress-bg.png","player-progress-fill.png");
	_progress->setPosition(RectUtil::left().x + _progress->getContentSize().width/2, RectUtil::top().y - _progress->getContentSize().height/2);
	this->addChild(_progress);

	auto pauseItem = MenuUtil::createMenuItemImage("pause1.png", "pause2.png", CC_CALLBACK_1(MainLayer::onTouchPause,this));
	pauseItem->setTag(1);
	pauseItem->setPosition(RectUtil::right().x - pauseItem->getContentSize().width/2, 
							RectUtil::top().y - pauseItem->getContentSize().height/2);

	auto debugItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
										CC_CALLBACK_1(MainLayer::toggleDebug, this));
    debugItem->setScale(2.0);
	debugItem->setPosition(Vec2(RectUtil::right().x - debugItem->getContentSize().width - pauseItem->getContentSize().width ,
		RectUtil::top().y - debugItem->getContentSize().height));

	
	auto menu = Menu::create(pauseItem, debugItem, NULL);
	menu->setPosition(0,0);
	this->addChild(menu, 20);
}

void MainLayer::addListener()
{
	//_eventDispatcher = Director::getInstance()->getEventDispatcher();

	_listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

	_listener_contact = EventListenerPhysicsContact::create();
	_listener_contact->onContactBegin = CC_CALLBACK_1(MainLayer::onContactBegin,this);
	_listener_contact->onContactSeperate = CC_CALLBACK_1(MainLayer::onContactSeperate,this);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_contact, 10);
}

void MainLayer::update(float dt)
{
	
}

bool MainLayer::onContactBegin(const PhysicsContact& contact)
{
	CCLOG("MainLayer::onContactBegin");
	auto npc_a = (Npc*)contact.getShapeA()->getBody()->getNode(); 
	auto npc_b = (Npc*)contact.getShapeB()->getBody()->getNode();
	Player* player = NULL;
	Monster* empty = NULL;
	if (npc_a->getType() == Npc::NpcType::PLAYER)
	{
		player = dynamic_cast<Player*>(npc_a);
		empty = dynamic_cast<Monster*>(npc_b);
	}
	else if (npc_b->getType() == Npc::NpcType::PLAYER)
	{
		player = dynamic_cast<Player*>(npc_b);
		empty = dynamic_cast<Monster*>(npc_a);
	}
	if (player) 
	{
		player->attack();
	}
	return true;
}

void MainLayer::onContactSeperate(const PhysicsContact& contact)
{
}