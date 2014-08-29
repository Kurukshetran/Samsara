#ifndef __GAME_SCENES_H__
#define __GAME_SCENES_H__

#include "HUDLayer.h"
#include "BaseMap.h"
#include "Hero.h"


class GameScenes : public cocos2d::Layer, public HudDelegate
{
	CREATE_FUNC(GameScenes);
	CC_SYNTHESIZE(HUDLayer*, _HUDLayer, HUDLayer);
	CC_SYNTHESIZE(BaseMap*, _baseMap, BaseMap);
	CC_SYNTHESIZE(Hero*, _hero, Hero);

public:
	GameScenes(void);
	~GameScenes(void);

	// ʵ��Delegate���鷽��
	void onWalk(cocos2d::Point direction, float distance);
	void onJump();
	void onFalled(Hero* hero);
	void onStop();
	void onSamsara();

	void SRWalk(Hero* hero, cocos2d::Point direction, float distance);
	void SRJump(Hero* hero);
	void SRFalled(Hero* hero);
	void SRStop(Hero* hero);
	void SRSamsara(Hero* hero);

	
	static cocos2d::Scene* createScene();
	virtual bool init(); 
	void addHeroToList(Hero* hero){ 	_allHeros.push_back(hero); }
	void update (float dt);
	void updateHeros(Hero* hero);
	void updateHerosEachother();

	bool CheckCollisionByType(Point pos, int type);
	bool CheckCollisionByTypeEx(Point pos, int type, Point& outPos);
	bool isMidair(cocos2d::Point heroPos);

	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	float _lastDistance;


	// begin ֮ǰ����궯����¼��� ��
	float _timeline;
	OneSamsaraAR _thisSamsaraAR;	// �������Ƕ���¼��
	SamsaraHeroList _samsaraHeros;	// ���ǵ������
	// end ֮ǰ����궯����¼���   ��

	HerosList _allHeros;
};

#endif