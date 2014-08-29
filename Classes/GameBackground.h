#ifndef __GAME_BACKGROUND__
#define __GAME_BACKGROUND__

#include "cocos2d.h"

class GameBackground : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameBackground);

	GameBackground(void);
	~GameBackground(void);

	virtual bool init(); 
	void update (float dt);

private:

	typedef std::map<float, cocos2d::Sprite* > CloudArr;
	CloudArr _cloudSprites;
	//cocos2d::Map< cocos2d::Sprite*, float >   _cloudSprites;
};

#endif //