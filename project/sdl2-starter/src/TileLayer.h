#ifndef __TileLayer__
#define __TileLayer__
#include "Game.h"


class TileLayer : public Layer 
{
private:
    int m_numColumns; 
    int m_numRows; 
    int m_tileSize;
    const vector<Tileset> &m_tilesets; 
    Vector2D m_position; 
    Vector2D m_velocity;  
    vector<vector<int>> m_tileIDs;
public:
    TileLayer(int tileSize, const vector<Tileset> &tilesets);
    virtual void update();
    virtual void render();
    void setTileIDs(const vector<vector<int>> &data) { m_tileIDs = data; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; } 
    Tileset getTilesetByID(int tileID);
};

#endif // define __TileLayer__