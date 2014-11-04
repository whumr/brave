#ifndef __MenuUtil_H__
#define __MenuUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class MenuUtil
{
public:
    static MenuItemImage* createMenuItemImage(const char* normal, const char* selected, ccMenuCallback callback)
	{
		auto item = MenuItemImage::create();
		auto nsf = SpriteFrameCache::getInstance()->getSpriteFrameByName(normal);
		auto ssf = SpriteFrameCache::getInstance()->getSpriteFrameByName(selected);
		item->setNormalSpriteFrame(nsf);
		item->setSelectedSpriteFrame(ssf);
		item->setCallback(callback);
		return item;
	}
};

#endif 