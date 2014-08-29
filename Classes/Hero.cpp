#include "Hero.h"
#include "FilesPCH.h"

Hero::Hero(void)
: _curState(eHero_idle)
, _heroType(eHero_true)
, _isJumping(false)
, _curDirection(eHDirectionRight)
{
}

Hero::~Hero(void)
{
}

Hero* Hero::create(HeroType type)
{
	Hero *ret = new Hero();

	ret->setHeroType(type);

	if (ret && ret->init())
	{
		ret->autorelease();

		return ret;
	}

	CC_SAFE_DELETE(ret);

	return NULL;
}

bool Hero::init()
{
	if (_heroType == eHero_true)
	{
		Sprite::initWithFile("hero_idle.png");
	}else
	{
		Sprite::initWithFile("hero_soul_idle.png");
	}
	
	_velocity = Point(0,0);

	return true;
}

bool Hero::changeState(HeroStates state)
{
	if (state == _curState)
		return false;

	// 某些状态不能直接切换过去。
	switch(state)
	{
	case eHero_idle:
		if (_curState == eHero_jump)
			return false;
		break;
	case eHero_walk:
		if (_curState == eHero_jump)
			return false;
		break;
	case eHero_jump:

		break;
	}

	
	Sprite::stopAllActions();
	_curState = state;

	return true;
}

void Hero::walk()
{
	if( !changeState(eHero_walk))
		return;

	if (_heroType == eHero_true)
	{
		Sprite::runAction(RepeatForever::create(GAnimationMgr->createAnimate(eAniTrueHero)));
	}else
	{
		Sprite::runAction(RepeatForever::create(GAnimationMgr->createAnimate(eAniHeroSoul)));
	}
}

bool Hero::jump()
{
	if( !changeState(eHero_jump))
		return false;

	if (_heroType == eHero_true)
	{
		Sprite::setTexture("hero_jump.png");
	}else
	{
		Sprite::setTexture("hero_soul_jump.png");
	}

	return true;
}

void Hero::falled()
{
	_curState = eHero_idle;

	if (_heroType == eHero_true)
	{
		Sprite::setTexture("hero_idle.png");
	}else
	{
		Sprite::setTexture("hero_soul_idle.png");
	}
}

void Hero::idle()
{
	if( !changeState(eHero_idle))
		return;

	if (_heroType == eHero_true)
	{
		Sprite::setTexture("hero_idle.png");
	}else
	{
		Sprite::setTexture("hero_soul_idle.png");
	}

}
