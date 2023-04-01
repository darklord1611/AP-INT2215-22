#ifndef __LevelParser__
#define __LevelParser__
#include "Level.h"
#include "tinyxml.h"
#include "Game.h"
#include "TileLayer.h"
#include "Base64.h"
#include <zlib/zconf.h>
#include <string>
class LevelParser 
{
private:
    int m_tileSize; 
    int m_width; 
    int m_height;
    void parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTileSets);
    void parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTileSets);
public:
    Level* parseLevel(string levelFile);
}; 

#endif // define __LevelParser__