#ifndef __BASE_MAP_H__
#define __BASE_MAP_H__

#include "cocos2d.h"

class BaseMap : public cocos2d::TMXTiledMap
{
	
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXLayer*, _groundLayer, GroundLayer);		// ��ͼ��ʾ��
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXLayer*, _metaLayer, MetaLayer);			// ��ͼ���������
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXObjectGroup*, _objectLayer, ObjectLayer);  // ��ͼ��ײ����

public:
	BaseMap(void);
	~BaseMap(void);
	static BaseMap* create(const std::string& tmxFile);
	virtual bool init();

	cocos2d::Point screenToTileCoord(cocos2d::Point position);

private:
	cocos2d::Size _tileSize;		// ��ͼ��ÿ��ĳߴ�
	cocos2d::Size _mapSize;		// ��ͼͼ��
};

#endif
