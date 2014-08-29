#pragma once
#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;

enum {
	kTagParentNode = 1,
};
class Box2DTest : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	Box2DTest(void);
	~Box2DTest(void);

	virtual bool init();

	void addSpriteAt(Point p);
	void update(float dt);

	void createResetButton();

	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
	CREATE_FUNC(Box2DTest);
protected:
	b2World* _world;
	Texture2D*_spriteTexture;
};

