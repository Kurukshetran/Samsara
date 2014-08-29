#include "FilesPCH.h"

BaseMap::BaseMap(void)
: _groundLayer(NULL)
, _metaLayer(NULL)
, _objectLayer(NULL)
{
}

BaseMap::~BaseMap(void)
{
}

BaseMap* BaseMap::create(const std::string& tmxFile)
{
	BaseMap *ret = new BaseMap();
	if (ret && ret->initWithTMXFile(tmxFile))
	{
		ret->init();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool BaseMap::init()
{
	_tileSize = this->getTileSize();
	_mapSize  = this->getMapSize();

	_groundLayer = this->getLayer("GroundLayer");
	_metaLayer = this->getLayer("MetaLayer");
	_metaLayer->setVisible(false);
	CCASSERT(NULL != _metaLayer, "'_metaLayer' not found");

	_objectLayer = this->getObjectGroup("Objects");
	CCASSERT(NULL != _objectLayer, "'_objectLayer' object group not found");

	return true;
}

Point BaseMap::screenToTileCoord(Point position)
{
	int x = position.x / _tileSize.width;
	int y = ((_tileSize.height * _mapSize.height) - position.y) / _tileSize.height;

	return Point(x, y);
}