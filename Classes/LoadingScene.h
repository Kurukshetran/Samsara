#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	
	CREATE_FUNC(LoadingScene);

	//LoadingScene();

	//~LoadingScene();

    virtual bool init();  

	void PreLoadRes();

	void PreloadMusic();

	void loadingDone(Node* pNode);

	// void loadCallBack(cocos2d::CCObject* object);//异步加载完成后回调主程序的函数
    

private:
	int count;//加载计数  
	int total;//总资源个数  
};

#endif
