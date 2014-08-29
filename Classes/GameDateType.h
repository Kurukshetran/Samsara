#ifndef _GAME_DATE_TYPE_H_
#define _GAME_DATE_TYPE_H_
#include "cocos2d.h"
USING_NS_CC;

class Hero;

// бя Enum бя 
enum HeroStates
{
	eHero_none,
	eHero_idle,
	eHero_walk,
	eHero_jump,
};

enum HeroType
{
	eHero_true,
	eHero_soul,
};

enum AnimationType	// add a animation step1
{
	eAniTrueHero,
	eAniHeroSoul,
	eAniHeroJump,
	eAniDestnation,
	eAniHeroExplode,
	eAniDestnationEx,
};

enum HDirection
{
	eHDirectionRight,
	eHDirectionLeft,	
};


// бя Struct бя 
typedef struct tagActionRecord
{ 
	enum ARtype
	{
		AR_WALK,
		AR_Jump,
		AR_STOP,
		AR_SAMSARA
	}type;

	float          keyTime;
	cocos2d::Point direction;
	float          distance;

} ActionRecord, *pActionRecord;

typedef std::vector<ActionRecord>   OneSamsaraAR;

typedef struct tagSamsaraHero 
{
	Hero* arHero;
	OneSamsaraAR ar;
	OneSamsaraAR::iterator arIter;
}SamsaraHero, *pSamsaraHero;

typedef std::vector<SamsaraHero> SamsaraHeroList;
typedef std::vector< Hero* > HerosList;


// define
const float HeroCollideWidthToAnchor = 10;
const float HeroCollideDownToAnchor = 4;


#endif