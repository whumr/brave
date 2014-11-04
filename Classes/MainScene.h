#ifndef __MainScene_H__
#define __MainScene_H__

#include "cocos2d.h"

USING_NS_CC;

class MainScene : public Scene
{
public:
	
    bool init();  
	void addUI();
	void onEnter();
	void onExit();
	void onTouchPause(Ref* sender);
	void onTouchResume();
	CREATE_FUNC(MainScene);
};

#endif 