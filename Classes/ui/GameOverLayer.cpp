#include "ui/GameOverLayer.h"

bool GameOverLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Sprite* background = Sprite::createWithSpriteFrameName("pause-bg.png");
	background->setPosition(RectUtil::center());
	this->addChild(background);

	auto size = background->getContentSize();
	auto title = Sprite::createWithSpriteFrameName("gameover-title.png");
	title->setPosition(size.width/2, size.height);
	background->addChild(title);

	auto homeItem = MenuUtil::createMenuItemImage("home-1.png","home-2.png",
													CC_CALLBACK_1(GameOverLayer::home,this));

	homeItem->setPosition(size.width/2, size.height/2);

	auto menu = Menu::create(homeItem,  NULL);
	menu->setPosition(RectUtil::leftBottom());

	_label = Label::createWithSystemFont("","fonts/Marker Felt.ttf",34);
	_label->setPosition(size.width/2,size.height);
	background->addChild(_label);

	background->addChild(menu);


	return true;
}

void GameOverLayer::home(Ref* obj)
{
	//auto main = dynamic_cast<MainScene*>(this->getParent());
	//main->onTouchResume();
	this->removeFromParentAndCleanup(true);
	auto start = StartScene::create();
	Director::getInstance()->replaceScene(start);
}

void GameOverLayer::setText(const std::string& text)
{
	_label->setString(text);
}