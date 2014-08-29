#include "FilesPCH.h"

// #include "LoadingScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading.plist");

	// 同步加载Loading资源

    // Loading background
	auto sprite = Sprite::createWithSpriteFrameName("LodingBG.jpg");

    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);

	// Loading text
	auto label = Label::createWithSystemFont("Loading ...", "Arial", 24);

	label->setPosition(Point(origin.x + label->getContentSize().width / 2 + 5,
		origin.y + label->getContentSize().height));

	this->addChild(label, 1);

	// loading animation
	auto loading = Sprite::createWithSpriteFrameName("Loading01.png");
	loading->setPosition(Point(visibleSize.width/2,visibleSize.height/2-50));
	this->addChild(loading);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 1; i <= 12; i++)
	{
		char szName[100] = {0}; 
		sprintf(szName, "Loading%02d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
	}
	auto animate = Animate::create(animation);
	auto repeat = Repeat::create(animate,1.5);
	auto repeatdone = CallFuncN::create(CC_CALLBACK_1(LoadingScene::loadingDone,this));
	auto sequence = Sequence::create(repeat, repeatdone, nullptr);
	loading->runAction(sequence);



	// 异步加载游戏资源。
	// 纹理
	PreLoadRes();

	// 音效
	PreloadMusic();

    return true;
}

void LoadingScene::PreLoadRes()
{
	GAnimationMgr->initAnimations();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist");
}

void LoadingScene::PreloadMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3",true);
}

void LoadingScene::loadingDone(Node* pNode)
{
	auto pScene = GameScenes::createScene();
	auto animateScene = TransitionFade::create(1.0f,pScene);
	Director::getInstance()->replaceScene(animateScene);
}