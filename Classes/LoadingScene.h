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

	// void loadCallBack(cocos2d::CCObject* object);//�첽������ɺ�ص�������ĺ���
    

private:
	int count;//���ؼ���  
	int total;//����Դ����  
};

#endif
