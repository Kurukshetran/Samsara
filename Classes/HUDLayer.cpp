#include "HUDLayer.h"
USING_NS_CC;

HUDLayer::HUDLayer(void)
: _delegator(NULL)
{
}


HUDLayer::~HUDLayer(void)
{
}

bool HUDLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HUDLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HUDLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HUDLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Sneaky button
	auto jumpBtn = MenuItemImage::create("joystick/SneakyBtnNormal.png", "joystick/SneakyBtnDown.png", CC_CALLBACK_1(HUDLayer::CallbackJump, this));
	auto SamsaraBtn = MenuItemImage::create("joystick/SneakyBtnNormal.png", "joystick/SneakyBtnDown.png", CC_CALLBACK_1(HUDLayer::CallbackSamsara, this));
	jumpBtn->setPosition(Point(origin.x + visibleSize.width - 150 ,	origin.y + 100) );
	SamsaraBtn->setPosition(Point(origin.x + visibleSize.width - 80 , origin.y + 240) );
	
	auto menu = Menu::create(jumpBtn, SamsaraBtn, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	// joystick
	_joystick = Sprite::create("joystick/joystick.png");
	_joystickBG = Sprite::create("joystick/joystick_bg.png");
	this->addChild(_joystick);
	this->addChild(_joystickBG);

	inactivityJoystick();

	return true;
}

bool HUDLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point location = touch->getLocation();

	if (location.x < winSize.width / 2)			// ��Ļ������Ӧ���ݸ�
	{
		activityJoystick(location);
	}

	return true;
}

void HUDLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point startPos = touch->getStartLocation();

	if (startPos.x > winSize.width / 2)         // ��Ļ������Ӧ���ݸ�
	{
		return;
	}
	
	Point location = touch->getLocation();
	float distance = startPos.getDistance(location);

	Point direction = (location - startPos).normalize();

	updateJoystick(direction, distance);
	float level = distance > ( _joystick->getContentSize().width + _joystickBG->getContentSize().width) / 2 ? 2.0f : 1.5f ; // �ٶȷ�����
	distance = (direction.x > 0 ? level : -level) * 1;	// �ٶ�ϵ��
	_delegator->onWalk(direction, distance);	// ί�ж����� Action Walk.
}

void HUDLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	if (_joystickBG->isVisible())
	{
		inactivityJoystick();
		_delegator->onStop();					// ί�ж����� Action Idle.
	}
}
void HUDLayer::CallbackJump(cocos2d::Ref* pSender)
{
	_delegator->onJump();						// ί�ж����� Action Jump.
}

void HUDLayer::CallbackSamsara(cocos2d::Ref* pSender)
{
	_delegator->onSamsara();					// ί�ж����� Logic Samsara.
}

void HUDLayer::activityJoystick(cocos2d::Point pos)
{
	_joystick->setPosition(pos);
	_joystickBG->setPosition(pos);
	_joystick->setVisible(true);
	_joystickBG->setVisible(true);
}

void HUDLayer::inactivityJoystick()
{
	_joystick->setPosition(_joystickBG->getPosition());
	_joystick->setVisible(false);
	_joystickBG->setVisible(false);
}

void HUDLayer::updateJoystick(cocos2d::Point direction, float distance)
{
	Point start = _joystickBG->getPosition();
	float joystickWidth = _joystick->getContentSize().width;
	float joystickBGWidth = _joystickBG->getContentSize().width;

	if (distance < joystickWidth / 2)	// �ƶ�û��ҡ�����ĵ�СԲ.
	{
		_joystick->setPosition(start + (direction * distance));
	}else if(distance > (joystickWidth + joystickBGWidth)/2 ) // �ƶ���������, СԲ��Բ��ֻ�ڻ�����Ե�ƶ�.
	{
		_joystick->setPosition(start + (direction * joystickBGWidth/2) );
	}else // �ڻ��������ƶ�
	{
		_joystick->setPosition(start + (direction * joystickWidth/2) );
	}
}
