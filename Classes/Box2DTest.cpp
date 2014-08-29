#include "Box2DTest.h"
#include "cocos-ext.h"
#include "VisibleRect.h"

#define PTM_RATIO 32

USING_NS_CC_EXT;

Scene* Box2DTest::createScene()
{
	auto scene = Scene::create();

	auto layer = Box2DTest::create();

	scene->addChild(layer);

	return scene;
}

Box2DTest::Box2DTest(void):
	_world(nullptr),
	_spriteTexture(nullptr)
{
}

Box2DTest::~Box2DTest(void)
{
	CC_SAFE_DELETE(_world);
}

bool Box2DTest::init()
{
	// Add Event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesEnded = CC_CALLBACK_2(Box2DTest::onTouchesEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// inti physics
	b2Vec2 gravity(0.0f, -5.0f);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;
	// bottom
	groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	// top
	groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	// left
	groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	// right
	groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);


	// Reset | Again
	createResetButton();

	// add background
	auto sprite = Sprite::create("Images/fantasyScene.png");
	sprite->setPosition( VisibleRect::center() );
	this->addChild(sprite, 0);

	// use batch node 
	auto parent = SpriteBatchNode::create("Images/blocks.png", 100);
	_spriteTexture = parent->getTexture();
	addChild(parent, 0, kTagParentNode);

	// init sprite
	addSpriteAt(VisibleRect::center());

	scheduleUpdate();

	return true;
}

void Box2DTest::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	_world->Step(dt, velocityIterations, positionIterations);
}

void Box2DTest::addSpriteAt(Point p)
{
	 CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);

	 b2BodyDef bodyDef;
	 bodyDef.type = b2_dynamicBody;
	 bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);

	 b2Body* body = _world->CreateBody(&bodyDef);

	 b2PolygonShape dynamicBox;
	 dynamicBox.SetAsBox(.5f, .5f);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &dynamicBox;
	 fixtureDef.density = 3.0f;
	 fixtureDef.friction = 0.2f;
	 body->CreateFixture(&fixtureDef);

	 auto parent = this->getChildByTag(kTagParentNode);
	 int idx = (CCRANDOM_0_1() > .5 ? 0:1);
	 int idy = (CCRANDOM_0_1() > .5 ? 0:1);
	 auto sprite = PhysicsSprite::createWithTexture(_spriteTexture,Rect(32 * idx,32 * idy,32,32));
	 parent->addChild(sprite);
	 sprite->setB2Body(body);
	 sprite->setPTMRatio(PTM_RATIO);
	 sprite->setPosition(p);
}

void Box2DTest::createResetButton()
{
	auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", [](Ref *sender){
		auto scene = Box2DTest::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	auto menu = Menu::create(reset, NULL);
	menu->setPosition(Point(VisibleRect::right().x - 30, VisibleRect::top().y - 30));
	this->addChild(menu);
}

void Box2DTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	for (auto& touch : touches)
	{
		if(!touch)
			break;

		auto location = touch->getLocation();

		addSpriteAt( location );
	}
}