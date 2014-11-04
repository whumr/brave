#include "MainScene.h"
#include "ui/MainLayer.h"
#include "ui/Background.h"
#include "ui/PauseLayer.h"

bool MainScene::init()
{
	if(!Scene::initWithPhysics())
		return false;
	this->addUI();
	return true;
}

void MainScene::onEnter()
{
	Scene::onEnter();
	// set gravity to zero
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
}

void MainScene::onExit()
{
	Scene::onExit();
	// set gravity to zero
	//this->getPhysicsWorld()->setGravity(Vec2(0, 0));
}

void MainScene::addUI()
{
	//backgound setup
	auto background = Background::create();
	background->setPosition(Point::ZERO);
	this->addChild(background);

	//main layer
	auto mainLayer = MainLayer::create();
	mainLayer->setPosition(Point::ZERO);
	mainLayer->setPhysicsWorld(this->getPhysicsWorld());
	this->addChild(mainLayer);
}

void MainScene::onTouchPause(Ref* sender)
{
	Director::getInstance()->pause();
	auto layer = PauseLayer::create();
	this->addChild(layer,10000);
}

void MainScene::onTouchResume()
{
	Director::getInstance()->resume();
}