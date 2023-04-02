#ifndef __LevelParser__
#define __LevelParser__
#include "tinyxml.h"
#include "Level.h"
#include "Base64.h"
#include "TileLayer.h"
#include "TextureManager.h"
#include <zlib/zlib.h>

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