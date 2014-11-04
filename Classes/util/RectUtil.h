#ifndef __RectUtil_H__
#define __RectUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class RectUtil
{
public:
	static Rect getVisibleRect();
	static Vec2 left();
	static Vec2 right();
	static Vec2 top();
	static Vec2 bottom();
	static Vec2 center();
	static Vec2 leftTop();
	static Vec2 rightTop();
	static Vec2 leftBottom();
	static Vec2 rightBottom();

private:
	static Rect s_visibleRect;
	static void lazyInit();
};

#endif 