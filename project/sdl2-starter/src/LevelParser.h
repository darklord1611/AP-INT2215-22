#ifndef __LevelParser__
#define __LevelParser__
#include "Level.h"
#include "tinyxml.h"
#include <string>
class LevelParser 
{
private:
    int m_tileSize; 
    int m_width; 
    int m_height;
    void parseTileSets(TiXmlElement* pTilesetRoot, vector<tileSet>* pTileSets);
    void parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<tileSet>* pTileSets);
public:
    Level* parseLevel(string levelFile);
}; 

#endif // define __LevelParser__