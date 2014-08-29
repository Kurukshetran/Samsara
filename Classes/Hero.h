#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "GameDateType.h"

class Hero : public cocos2d::Sprite
{
public:
	Hero(void);
	~Hero(void);

	static Hero* create( HeroType type); // EF_TEMP type
	virtual bool init();

	void walk();
	bool jump();
	void falled();
	void idle();

public:
	bool changeState(HeroStates state);
	HeroStates getState() { return _curState; }

	cocos2d::Point& getVelocity() { return _velocity; }

private:
	HeroStates _curState;
	cocos2d::Point _velocity;

	CC_SYNTHESIZE(HeroType, _heroType, HeroType);
	CC_SYNTHESIZE(HDirection, _curDirection, HDirection);
	CC_SYNTHESIZE(bool, _isJumping, IsJumping);
};

#endif