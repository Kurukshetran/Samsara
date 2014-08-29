#include "FilesPCH.h"
USING_NS_CC;



//产生一个从start到end间的随机数
float RandomBetween(float start,float end)
{
	return CCRANDOM_0_1()*(end-start)+start; 
}

GameBackground::GameBackground(void)
{
}


GameBackground::~GameBackground(void)
{
}

bool GameBackground::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point origin = Director::getInstance()->getVisibleOrigin();

	// background sky
	auto blueSky = Sprite::createWithSpriteFrameName("BlueSky.png");

	blueSky->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->addChild(blueSky);

	// background clouds
	for (int i = 1; i <= 8; i++)
	{
		char szName[100] = {0}; 

		sprintf(szName, "Cloud%d.png", i);

		auto spr = Sprite::createWithSpriteFrameName(szName);

		// Map<Key，Value>     Key:移动速度。 Value：云图片精灵指针
		float scale = 0.0f;
		if (i < 5)
		{
			scale = RandomBetween(0.3,0.5);	// far
			spr->setScale(scale);
			_cloudSprites[ scale * 0.8 ] = spr;
		}
		else
		{
			scale = RandomBetween(0.6,0.9); // near
			spr->setScale(scale);
			_cloudSprites[ scale * 0.6 ] = spr;
		}

		spr->setPosition(Point(visibleSize.width * RandomBetween(0,1)  + origin.x, visibleSize.height * RandomBetween(0.3,1) + origin.y));
		
		this->addChild(spr);
	}


	this->scheduleUpdate();

	return true;
}

void GameBackground::update (float dt)
{
	if(!_cloudSprites.empty())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		CloudArr::iterator iter = _cloudSprites.begin();

		for (;iter != _cloudSprites.end(); iter++)
		{
			auto spr = iter->second;
			auto pos = spr->getPosition();

			if (pos.x < -spr->getContentSize().width * iter->first / 2)
				spr->setPosition(Point( spr->getContentSize().width / 2 + visibleSize.width, visibleSize.height * RandomBetween(0.3,1)));
			else
				spr->setPosition(Point( pos.x - iter->first, pos.y));
		}
	}
}