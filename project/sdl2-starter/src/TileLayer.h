#ifndef __TileLayer__
#define __TilePayer__
#include "Layer.h"
#include "Vector2D.h"

class TileLayer : public Layer 
{
private:
    int m_numColumns; 
    int m_numRows; 
    int m_tileSize; 
    Vector2D m_position; 
    Vector2D m_velocity; 
    const vector<Tileset> &m_tilesets; 
    vector<vector<int>> m_tileIDs;
public:
    TileLayer(int tileSize, const vector<Tileset> &tilesets);
    virtual void update();
    virtual void render();
    void setTileIDs(const vector<vector<int>> &data) { m_tileIDs = data; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; } 
    tileSet getTilesetByID(int tileID);
};

#endif // define __Layer__