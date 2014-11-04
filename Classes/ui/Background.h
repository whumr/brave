#ifndef __Background_H__
#define __Background_H__
#include "cocos2d.h"
#include "util/RectUtil.h"

USING_NS_CC;

class Background : public Layer
{
public:
	bool init();
	CREATE_FUNC(Background);
	void move(const char* direction, Sprite* withSprite);
	void onMoveEnd();
private:
	bool _isMoving;
	Sprite* _spriteA;
	Sprite* _spriteB;
};


#endif