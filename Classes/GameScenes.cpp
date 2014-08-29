#include "GameScenes.h"
#include "FilesPCH.h"
#include "CCDrawingPrimitives.h"

GameScenes::GameScenes(void)
: _timeline(0.0f)
{
	_allHeros.clear();
}


GameScenes::~GameScenes(void)
{
}


Scene* GameScenes::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScenes::create();

	scene->addChild(layer);

	// tilemap
	auto tilemap = BaseMap::create("samsara01.tmx");

	scene->addChild(tilemap);

	layer->setBaseMap(tilemap);

	// get hero position
	auto spawnPoint = tilemap->getObjectLayer()->getObject("SpawnPoint");
	
	// hero
	auto hero = Hero::create(eHero_true);

	hero->setAnchorPoint(Point(0.5f, 0.07));

	hero->setPosition(spawnPoint["x"].asInt(), spawnPoint["y"].asInt());

	scene->addChild(hero);

	layer->setHero(hero);

	layer->addHeroToList(hero);

	// control
	auto hudLayer = HUDLayer::create();

	scene->addChild(hudLayer);

	hudLayer->setDelegator(layer);

	layer->setHUDLayer(hudLayer);


	// Destnation Anim
	auto destPos = tilemap->getObjectLayer()->getObject("Destnation");

	auto dest1 = GAnimationMgr->createAnimateSpriteByType(eAniDestnationEx);
	dest1->setPosition(destPos["x"].asInt(), destPos["y"].asInt());
	// dest1->setScale(0.9f);
	scene->addChild(dest1);
	dest1->runAction(RepeatForever::create(GAnimationMgr->createAnimate(eAniDestnationEx)));


	return scene;
}

// on "init" you need to initialize your instance
bool GameScenes::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto bg = GameBackground::create();

	this->addChild(bg);

	this->scheduleUpdate();

	return true;
}


void GameScenes::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void GameScenes::onWalk(cocos2d::Point direction, float distance)
{
	bool isleft = direction.x < 0 ;
	if (distance == _lastDistance)
	{
		if ( isleft && _hero->getHDirection() == eHDirectionLeft )
			return;
		else if ( !isleft && _hero->getHDirection() == eHDirectionRight)
			return;
	}
	
	
	isleft ? _hero->setHDirection(eHDirectionLeft) : _hero->setHDirection(eHDirectionRight);
	_hero->setFlipX( isleft );
	_hero->walk();

	_lastDistance = _hero->getVelocity().x = distance;

	// action video
	ActionRecord ar;
	ar.type = ActionRecord::AR_WALK;
	ar.keyTime = _timeline;
	ar.direction = direction;
	ar.distance = distance;
	_thisSamsaraAR.push_back(ar);
}

void GameScenes::onJump()
{
	if( _hero->jump() )
		_hero->getVelocity().y = 4;

	// action video
	ActionRecord ar;
	ar.type = ActionRecord::AR_Jump;
	ar.keyTime = _timeline;
	_thisSamsaraAR.push_back(ar);
}

void GameScenes::onStop()
{
	_hero->idle();
	_hero->getVelocity() = Point(0,0);
	_lastDistance = 0;

	// action video
	ActionRecord ar;
	ar.type = ActionRecord::AR_STOP;
	ar.keyTime = _timeline;
	_thisSamsaraAR.push_back(ar);
}

void GameScenes::onFalled(Hero* hero)
{
	hero->falled();
	hero->getVelocity().y = 0.0f;

	// action video。由碰撞被动置换的状态，不做动作录像
}

void GameScenes::onSamsara()
{
	// action video
	ActionRecord ar;
	ar.type = ActionRecord::AR_SAMSARA;
	ar.keyTime = _timeline;
	_thisSamsaraAR.push_back(ar);
	_hero->setVisible(false);


	// hero explode
	auto _heroExplode = GAnimationMgr->createAnimateSpriteByType(eAniHeroExplode);
	this->addChild(_heroExplode);
	_heroExplode->setPosition(_hero->getPosition().x, _hero->getPosition().y);

	auto sequence = Sequence::create(
	Animate::create(GAnimationMgr->getAnimation(eAniHeroExplode))
	,
	CallFunc::create([=]()
	{  
		SamsaraHero samHero;
		auto hero = Hero::create(eHero_soul);
		hero->setAnchorPoint(Point(0.5f, 0.07));
		this->addChild(hero);

		samHero.arHero = hero;
		samHero.ar     = _thisSamsaraAR;
		_samsaraHeros.push_back(samHero);
		_allHeros.push_back(hero);

		auto spawnPoint = _baseMap->getObjectLayer()->getObject("SpawnPoint");
		for (auto it = _samsaraHeros.begin(); it != _samsaraHeros.end(); ++it)
		{
			it->arIter = it->ar.begin();
			it->arHero->setPosition(spawnPoint["x"].asInt(), spawnPoint["y"].asInt());
			it->arHero->falled();
		}

		_hero->setVisible(true);
		_hero->setPosition(spawnPoint["x"].asInt(), spawnPoint["y"].asInt());
		_thisSamsaraAR.clear();
		_timeline = 0.0f;

		this->removeChild(_heroExplode);

	}), NULL);

	_heroExplode->runAction(sequence); 

}

// 灵魂动作处理
void GameScenes::SRWalk(Hero* hero, cocos2d::Point direction, float distance)
{
	bool isleft = direction.x < 0 ;

	isleft ? hero->setHDirection(eHDirectionLeft) : hero->setHDirection(eHDirectionRight);
	hero->setFlipX( isleft );
	hero->walk();
	hero->getVelocity().x = distance;
}

void GameScenes::SRJump(Hero* hero)
{
	if( hero->jump() )
		hero->getVelocity().y = 4;
}

void GameScenes::SRFalled(Hero* hero)
{
	hero->falled();
	hero->getVelocity().y = 0.0f;
}

void GameScenes::SRStop(Hero* hero)
{
	hero->idle();
	hero->getVelocity() = Point(0.0f,0.0f);
}

void GameScenes::SRSamsara(Hero* hero)
{

}

void GameScenes::update (float dt)
{
	_timeline += dt;

	updateHeros(_hero);


	for (auto it = _samsaraHeros.begin(); it != _samsaraHeros.end(); ++it)
	{
		if ( it->arIter != it->ar.end() && it->arIter->keyTime < _timeline)
		{
			switch (it->arIter->type)
			{
			case ActionRecord::AR_Jump:
				SRJump(it->arHero);
				break;
			case ActionRecord::AR_STOP:
				SRStop(it->arHero);
				break;
			case ActionRecord::AR_WALK:
				SRWalk(it->arHero, it->arIter->direction, it->arIter->distance);
				break;
			default:
				break;
			}
			++(it->arIter);
		}

		updateHeros(it->arHero);
	}

	updateHerosEachother();
}

void GameScenes::updateHeros(Hero* hero)
{
	if (!hero)
		return;
	
	Size winSize = Director::getInstance()->getWinSize();
	Point heroPos = hero->getPosition();

	// 到达终点
	if ( CheckCollisionByType(heroPos, 2) )	// 到达终点
	{
		// NextLevel();
		auto pScene = GameScenes::createScene();
		auto animateScene = TransitionShrinkGrow::create(2.0f,pScene);
		Director::getInstance()->replaceScene(animateScene);

		return;
	}

	// update hero position
	switch (hero->getState())
	{
	case eHero_idle:
		break;
	case eHero_walk:
		{
			heroPos += hero->getVelocity();

			// 碰撞检测 左右

			if ( CheckCollisionByType(heroPos + Point(HeroCollideWidthToAnchor, 0), 1) 
				|| CheckCollisionByType(heroPos + Point(-HeroCollideWidthToAnchor, 0), 1) )
			{
				break;
			}

			if (isMidair(heroPos))
			{
				heroPos.y -= 5;
			}

			heroPos.x = clampf(heroPos.x, 20, winSize.width - 20);	// 屏幕边界
			hero->setPosition(heroPos);
		}
		break;
	case eHero_jump:
		{
			heroPos += hero->getVelocity();
			hero->getVelocity().y -= 0.15;  

			// 左右碰撞检测
			if ( CheckCollisionByType(heroPos + Point(HeroCollideWidthToAnchor, 0), 1) 
				|| CheckCollisionByType(heroPos + Point(-HeroCollideWidthToAnchor, 0), 1) )
			{
				heroPos.x -= hero->getVelocity().x;
			}

			// 是否触地
			Point tileCoord;
			if ( CheckCollisionByTypeEx(heroPos + Point(HeroCollideWidthToAnchor, -HeroCollideDownToAnchor), 1, tileCoord) )
			{
				heroPos.y = _baseMap->getTileSize().height * (_baseMap->getMapSize().height - tileCoord.y) + 2;
				onFalled(hero);
			}
			else if ( CheckCollisionByTypeEx(heroPos + Point(-HeroCollideWidthToAnchor, -HeroCollideDownToAnchor), 1, tileCoord) )
			{
				heroPos.y = _baseMap->getTileSize().height * (_baseMap->getMapSize().height - tileCoord.y) + 2;
				onFalled(hero);
			}

			heroPos.x = clampf(heroPos.x, 20, winSize.width - 20);	// 屏幕边界
			hero->setPosition(heroPos);
		}
		break;
	}
}

void GameScenes::updateHerosEachother()
{
	for (auto it = _allHeros.begin(); it != _allHeros.end(); ++it)
	{
		Hero* cur = *it;

		if ( cur->getState() == eHero_jump && cur->getVelocity().y < 0 )	// 满足条件才检测和别人的碰撞。
		{
			for (auto subIt = _allHeros.begin(); subIt != _allHeros.end(); ++subIt)
			{
				Hero* other = *subIt;

				if (it == subIt || abs( cur->getPosition().x - other->getPosition().x ) > HeroCollideWidthToAnchor )
				{
					continue;
				}else
				{
					// 应该和它检测碰撞。
					float tall = _hero->getContentSize().height;
					if( cur->getPosition().y > other->getPosition().y + tall && cur->getPosition().y + cur->getVelocity().y < other->getPosition().y + tall )
					{
						SRFalled(cur);
						Point heroPos = cur->getPosition();
						heroPos.y = other->getPosition().y + tall;
						cur->setPosition(heroPos);						
						return;
					}
				}
			}
		}
	}
}


bool GameScenes::CheckCollisionByType(Point pos, int type)		// 1 碰撞. 2 终点.
{

	Point tileCoord = _baseMap->screenToTileCoord(pos);

	int tileGid = _baseMap->getMetaLayer()->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		auto properties = _baseMap->getPropertiesForGID(tileGid).asValueMap();

		if (!properties.empty()) 
		{
			std::string collision;

			switch(type)
			{
			case 1:
				collision = properties["Collidable"].asString();
				break;

			case 2:
				collision = properties["Destination"].asString();
				break;
			}

			if ("true" == collision) 
			{
				return true;
			}
		}
	}

	return false;
}


bool GameScenes::CheckCollisionByTypeEx(Point pos, int type, Point& outPos)		// 1 碰撞. 2 终点.
{

	Point tileCoord = _baseMap->screenToTileCoord(pos);

	outPos = tileCoord;

	int tileGid = _baseMap->getMetaLayer()->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		auto properties = _baseMap->getPropertiesForGID(tileGid).asValueMap();

		if (!properties.empty()) 
		{
			std::string collision;

			switch(type)
			{
			case 1:
				collision = properties["Collidable"].asString();
				break;

			case 2:
				collision = properties["Destination"].asString();
				break;
			}

			if ("true" == collision) 
			{
				return true;
			}
		}
	}

	return false;
}

bool GameScenes::isMidair(cocos2d::Point heroPos )
{
	// 是否悬空了
	auto tileCoordr = _baseMap->screenToTileCoord(heroPos + Point(HeroCollideWidthToAnchor, -HeroCollideDownToAnchor));
	auto tileGidr = _baseMap->getMetaLayer()->getTileGIDAt(tileCoordr);

	auto tileCoordl = _baseMap->screenToTileCoord(heroPos + Point(-HeroCollideWidthToAnchor, -HeroCollideDownToAnchor));
	auto tileGidl = _baseMap->getMetaLayer()->getTileGIDAt(tileCoordl);

	if (!tileGidr && !tileGidl)
		return true;

	return false;
}