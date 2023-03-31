#ifndef __Level__
#define __Level__
#include <iostream>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
using namespace std;

struct tileSet 
{
    int firstGridID; 
    int tileWidth; 
    int tileHeight; 
    int spacing; 
    int margin; 
    int width; 
    int height; 
    int numColumns; 
    string name;
}

class Level 
{
private:
    vector<Layer*> m_layers;
    vector<tileSet> m_tileSets;
    friend class LevelParser; // allow levelparser to create new level
    Level();
public:
    ~Level() {}
    vector<tileSet>* getTileSets() { return &m_tileSets; }
    vector<Layer*>* getLayers() { return &m_layers; }
    void update();
    void render();    
};

#endif // define __Level__