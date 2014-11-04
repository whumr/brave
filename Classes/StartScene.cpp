#include "StartScene.h"

bool StartScene::init()
{
	if(!Scene::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist","image/role.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
	auto background = Sprite::create("image/start-bg.jpg");
	background->setPosition(RectUtil::center());
	this->addChild(background);


	auto start_item = MenuUtil::createMenuItemImage("start1.png", "start2.png", CC_CALLBACK_1(StartScene::onStart,this));
	auto menu = Menu::createWithItem(start_item);
	this->addChild(menu);

	auto position = RectUtil::leftBottom();
	position.y = position.y + 200;

	auto player = Player::create();
	player->setPosition(position.x + 200, position.y);
	player->playAnimationForever(Npc::AnimationType::ATTACKING);
	this->addChild(player);

	auto monster1 = Monster::create(Npc::NpcType::MONSTER1);
	monster1->setPosition(position.x + 400, position.y);
	monster1->playAnimationForever(Npc::AnimationType::ATTACKING);
	this->addChild(monster1);

	auto monster2 = Monster::create(Npc::NpcType::MONSTER2);
	monster2->setPosition(position.x + 600, position.y);
	monster2->playAnimationForever(Npc::AnimationType::ATTACKING);
	this->addChild(monster2);

	auto boss = Boss::create();
	boss->setPosition(position.x + 800, position.y);
	boss->playAnimationForever(Npc::AnimationType::ATTACKING);
	this->addChild(boss);

	return true;
}

void StartScene::onStart(Ref* obj)
{
	CCLOG("StartLayer::onStart");
	auto scene = MainScene::create();
	Director::getInstance()->replaceScene(scene);
}