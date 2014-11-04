#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__
#include "cocos2d.h"
#include "util/RectUtil.h"
#include "util/MenuUtil.h"
#include "StartScene.h"

USING_NS_CC;

class GameOverLayer : public Layer
{
public:
	bool init();
	CREATE_FUNC(GameOverLayer);

	void home(Ref* obj);
	void setText(const std::string& text);
private:
	Label* _label;
};


#endif