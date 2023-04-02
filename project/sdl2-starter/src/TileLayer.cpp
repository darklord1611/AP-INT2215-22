#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const vector<Tileset> &tilesets) :
m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0) 
{
    m_numColumns = (theGame::Instance()->getGameWidth() / m_tileSize);
    m_numRows = (theGame::Instance()->getGameHeight() / m_tileSize);
    cout << m_numColumns << " " << m_numRows << endl;
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
    for(int i = 0; i < m_numRows; i++) 
    {
        for(int j = 0; j < m_numColumns; j++) 
        {
            int id = m_tileIDs[i + x1][j + x1];
            if(id == 0) 
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;
            _TextureManager::Instance()->drawTile(tileset.name, 2, 2, (j * m_tileSize) - x2,
            (i * m_tileSize) - y2, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns,
            (id - (tileset.firstGridID - 1)) % tileset.numColumns, theGame::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) 
{
    for(int i = 0; i < m_tilesets.size();i++) 
    {
        if(i + 1 <= m_tilesets.size() - 1) 
        {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) 
            {
                return m_tilesets[i];
            }
        } else 
        {
            return m_tilesets[i];
        }
    }
    cout << "returning empty tileset" << endl;
    Tileset t;
    return t;
}