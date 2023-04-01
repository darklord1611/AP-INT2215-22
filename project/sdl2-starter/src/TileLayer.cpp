#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const vector<Tileset> &tilesets) :
m_tileSize(tileSize), m_tileSets(tilesets), m_position(0,0), m_velocity(0,0) 
{
    m_numColumns = (theGame::Instance()->getGameWidth() / m_tileSize);
    m_numRows = (theGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update() 
{
    m_position += m_velocity;
}

void TileLayer::render() 
{
    int x1, y1, x2, y2;
    x1 = m_position.getX() / m_tileSize;
    y1 = m_position.getY() / m_tileSize;
    x2 = int(m_position.getX()) % m_tileSize;   
    y2 = int(m_position.getY()) % m_tileSize;
    for(int i = 0; i < m_numRows;i++) 
    {
        for(int j = 0; j < m_numColumns;j++) 
        {
            int id = m_tileIDs[i][j + x];
            if(id == 0) 
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;
            
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) 
{

}