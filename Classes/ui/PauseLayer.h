#ifndef __PauseLayer_H__
#define __PauseLayer_H__
#include "cocos2d.h"

USING_NS_CC;

class PauseLayer : public LayerColor
{
public:
	bool init();
	void addUI();
	void addTouch();
	void home(Ref* obj);
	void back(Ref* obj);
	
	CREATE_FUNC(PauseLayer);
private:
	EventListenerTouchOneByOne* _listener;
};

#endif