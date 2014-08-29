#include "AnimationManager.h"

USING_NS_CC;

AnimationManager::AnimationManager(void)
{
}

AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::initAnimations()	// add a animation step2
{
	char temp[20] = { 0 };

	sprintf(temp, "%d", eAniTrueHero);	
	AnimationCache::getInstance()->addAnimation(
		createAnimationByType(eAniTrueHero), temp);

	sprintf(temp, "%d", eAniDestnation);	
	AnimationCache::getInstance()->addAnimation(
		createAnimationByType(eAniDestnation), temp);

	sprintf(temp, "%d", eAniHeroSoul);	
	AnimationCache::getInstance()->addAnimation(
		createAnimationByType(eAniHeroSoul), temp);

	sprintf(temp, "%d", eAniHeroExplode);	
	AnimationCache::getInstance()->addAnimation(
		createAnimationByType(eAniHeroExplode), temp);

	sprintf(temp, "%d", eAniDestnationEx);	
	AnimationCache::getInstance()->addAnimation(
		createAnimationByType(eAniDestnationEx), temp);

}

Animation* AnimationManager::createAnimationByType(AnimationType type)
{
	Vector<SpriteFrame*> vec;
	SpriteFrame* frame = NULL;
	Texture2D* texture = NULL;
	Animation* animation = NULL;
	 

	switch (type)	// add a animation step3
	{
	case eAniTrueHero:
		{
			texture = TextureCache::getInstance()->addImage("hero_walk.png");
			for (int i = 0; i < 4; ++i)
			{
				frame = SpriteFrame::createWithTexture(texture, CCRectMake(64*i, 0, 64, 47));
				vec.pushBack(frame);
			}
			animation = Animation::createWithSpriteFrames(vec, 0.15f);
			break;
		}
	case eAniHeroSoul:
		{
			texture = TextureCache::getInstance()->addImage("hero_soul_walk.png");
			for (int i = 0; i < 4; ++i)
			{
				frame = SpriteFrame::createWithTexture(texture, CCRectMake(64*i, 0, 64, 47));
				vec.pushBack(frame);
			}
			animation = Animation::createWithSpriteFrames(vec, 0.15f);
			break;
		}
	case eAniDestnation:
		{
			texture = TextureCache::getInstance()->addImage("destnation.png");
			for (int i = 0; i < 15; ++i)
			{
				frame = SpriteFrame::createWithTexture(texture, CCRectMake(32*i, 0, 32, 44));
				vec.pushBack(frame);
			}
			animation = Animation::createWithSpriteFrames(vec, 0.1f);
			break;
		}
	case eAniHeroExplode:
		{
			texture = TextureCache::getInstance()->addImage("hero_explode.png");
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					frame = SpriteFrame::createWithTexture(texture, CCRectMake(192*j, 192*i, 192, 192));
					vec.pushBack(frame);
				}
			}
			animation = Animation::createWithSpriteFrames(vec, 0.1f);
			break;
		}
	case eAniDestnationEx:
		{
			texture = TextureCache::getInstance()->addImage("destnationEx.png");
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					frame = SpriteFrame::createWithTexture(texture, CCRectMake(96*j, 96*i, 96, 96));
					vec.pushBack(frame);
				}
			}
			animation = Animation::createWithSpriteFrames(vec, 0.2f);
			break;
		}
	//case eAniHeroRight:
	//	{
	//		texture = TextureCache::getInstance()->addImage("hero_walk_right.png");
	//		for (int i = 0; i < 5; ++i)
	//		{
	//			frame = SpriteFrame::createWithTexture(texture, Rect(64*i, 0, 64, 64));
	//			vec.pushBack(frame);
	//		}
	//		animation = Animation::createWithSpriteFrames(vec, 0.05f);
	//		break;
	//	}
	}             

	return animation;
}


Sprite* AnimationManager::createAnimateSpriteByType(AnimationType type)
{
	switch (type)	// add a animation step4
	{
	case eAniTrueHero:
		{	
			return CCSprite::create("hero_walk.png", CCRectMake(0, 0, 64, 47));
			break;
		}
	case eAniHeroSoul:
		{
			return CCSprite::create("hero_soul_walk.png", CCRectMake(0, 0, 64, 47));
			break;
		}
	case eAniDestnation:
		{
			return CCSprite::create("destnation.png", CCRectMake(0, 0, 32, 44));
			break;
		}
	case eAniHeroExplode:
		{
			return CCSprite::create("hero_explode.png", CCRectMake(0, 0, 192, 192));
			break;
		}
	case eAniDestnationEx:
		{
			return CCSprite::create("destnationEx.png", CCRectMake(0, 0, 96, 96));
			break;
		}
	}
}

Animation* AnimationManager::getAnimation(AnimationType type)
{
	char temp[32] = { 0 };
	sprintf(temp, "%d", type);

	return AnimationCache::getInstance()->getAnimation(temp);
}

Animate* AnimationManager::createAnimate(const char *type)
{
	Animation *anim = AnimationCache::getInstance()->getAnimation(type);
	if (anim)
	{
		return Animate::create(anim);
	}
	return NULL;
}

Animate* AnimationManager::createAnimate(AnimationType type)
{
	Animation *anim = getAnimation(type);
	if (anim)
	{
		return Animate::create(anim);
	}
	return NULL;
}

AnimationManager* AnimationManager::getInstance()
{
	if (!_instance)
	{
		_instance = new AnimationManager();
	}
	return _instance;
}