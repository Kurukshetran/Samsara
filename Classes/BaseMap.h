#ifndef __BASE_MAP_H__
#define __BASE_MAP_H__

#include "cocos2d.h"

class BaseMap : public cocos2d::TMXTiledMap
{
	
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXLayer*, _groundLayer, GroundLayer);		// 地图显示层
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXLayer*, _metaLayer, MetaLayer);			// 地图上特殊对象
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXObjectGroup*, _objectLayer, ObjectLayer);  // 地图碰撞区域

public:
	BaseMap(void);
	~BaseMap(void);
	static BaseMap* create(const std::string& tmxFile);
	virtual bool init();

	cocos2d::Point screenToTileCoord(cocos2d::Point position);

private:
	cocos2d::Size _tileSize;		// 地图上每块的尺寸
	cocos2d::Size _mapSize;		// 地图图块
};

#endif
