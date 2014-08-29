#ifndef __ANIMATION_MANAGER_H__
#define __ANIMATION_MANAGER_H__

#include "cocos2d.h"
#include "GameDateType.h"


class AnimationManager
{
public:
	AnimationManager(void);
	~AnimationManager(void);

	void initAnimations();
	
	cocos2d::Animation* getAnimation(AnimationType type);
	cocos2d::Animate*   createAnimate(const char *type);
	cocos2d::Animate*   createAnimate(AnimationType type);
	cocos2d::Sprite* createAnimateSpriteByType(AnimationType type);

	static AnimationManager* getInstance();

private:
	cocos2d::Animation* createAnimationByType(AnimationType type);

};

static AnimationManager* _instance;
#define GAnimationMgr AnimationManager::getInstance()

#endif