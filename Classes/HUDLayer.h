#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__
#include "cocos2d.h"

class HudDelegate
{
public:
	virtual void onWalk(cocos2d::Point direction, float distance) = 0; 	// 移动，direction为向量，distance是与起点的直线距离

	virtual void onJump() = 0; 	// 跳跃

	virtual void onStop() = 0;

	virtual void onSamsara() = 0; // 转生
};

class HUDLayer : public cocos2d::Layer
{
public:
	HUDLayer(void);
	~HUDLayer(void);

	virtual bool init();
	CREATE_FUNC(HUDLayer);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
	void CallbackJump(cocos2d::Ref* pSender);
	void CallbackSamsara(cocos2d::Ref* pSender);

private:
	CC_SYNTHESIZE(HudDelegate*, _delegator, Delegator);

	cocos2d::Sprite*    _joystick;
	cocos2d::Sprite*    _joystickBG;

	// EF_TEMP Shoudle Add Button .

	void activityJoystick(cocos2d::Point pos);
	void inactivityJoystick();
	void updateJoystick(cocos2d::Point direction, float distance);
};


#endif
