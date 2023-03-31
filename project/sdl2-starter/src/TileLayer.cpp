#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const vector<tileSet> &tileSets) :
m_tileSize(tileSize), m_tileSets(tileSets), m_position(0,0), m_velocity(0,0) 
{

}

void TileLayer::update() 
{

}

void TileLayer::render() 
{
    
}

tileSet TileLayer::getTilesetByID(int tileID) 
{

}