#ifndef __Level__
#define __Level__
#include "Layer.h"
#include <iostream>
#include <vector>

using namespace std;

struct Tileset 
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
};

class Level     
{
private:
    vector<Layer*> m_layers;
    vector<Tileset> m_tilesets;
    friend class LevelParser; // allow levelparser to create new level
    Level() {}
public:
    ~Level() {}
    vector<Tileset>* getTilesets() { return &m_tilesets; }
    vector<Layer*>* getLayers() { return &m_layers; }
    void update();
    void render();    
};

#endif // define __Level__