#ifndef __StartScene__
#define __StartScene__
#include "cocos2d.h"
#include "util/RectUtil.h"
#include "util/MenuUtil.h"
#include "npc/Npc.h"
#include "npc/Player.h"
#include "npc/Monster.h"
#include "npc/Boss.h"
#include "MainScene.h"

USING_NS_CC;

class StartScene : public Scene
{
public:
	bool init();
	void onStart(Ref* obj);
	CREATE_FUNC(StartScene);
};

#endif