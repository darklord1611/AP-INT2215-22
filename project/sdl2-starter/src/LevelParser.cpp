#include "LevelParser.h"

Level* LevelParser::parseLevel(string levelFile) 
{
    // create a tinyxml document to load the map
    TiXmlDocument levelDocument;
    if(!levelDocument.LoadFile(levelFile.c_str())) 
    {
        cout << levelDocument.ErrorDesc() << endl;
    }
    // create a level object
    Level* pLevel = new Level();

    // get the root node
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // parse the tilesets
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object layers 
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) 
    { 
        if(e->Value() == string("layer")) 
        { 
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets()); 
        } 
    }

    return pLevel;
}


void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTileSets) 
{
    // first add the tileset to texture manager
    _TextureManager::Instance()->load("assets/" + (string)pTilesetRoot->FirstChildElement()->Attribute("source"),pTilesetRoot->Attribute("name"), theGame::Instance()->getRenderer());
    // create a tileset object
    Tileset tileset; 
    pTilesetRoot->FirstChildElement()->Attribute("width",&tileset.width); 
    pTilesetRoot->FirstChildElement()->Attribute("height",&tileset.height); 
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID); 
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth); 
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight); 
    pTilesetRoot->Attribute("spacing", &tileset.spacing); 
    pTilesetRoot->Attribute("margin", &tileset.margin); 
    tileset.name = pTilesetRoot->Attribute("name");
    pTilesetRoot->Attribute("columns", &tileset.numColumns);
    pTileSets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTileSets) 
{
    // create new tileLayer 
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTileSets);
    
    // tile data
    vector<vector<int>> data;
    string decodedIDs;
    TiXmlElement* pDataNode;

    // get data node to handle
    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) 
    {
        if(e->Value() == string("data")) 
        {
            pDataNode = e;
        }
    }
    
    // use base64 to decode
    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) 
    {
        TiXmlText* text = e->ToText();
        string t = text->Value(); 
        decodedIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf sizeOfIDs = m_width * m_height * sizeof(int); 
    vector<int> IDs(m_width * m_height);
    uncompress((Bytef*)&IDs[0], &sizeOfIDs,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    vector<int> layerRow(m_width);
    for(int i = 0; i < m_height;i++) 
    {
        data.push_back(layerRow);
    }
    for(int rows =  0; rows < m_height; rows++) 
    {
        for(int cols = 0; cols < m_width; cols++) 
        {
            data[rows][cols] = IDs[rows * m_width + cols];
        }
    }
    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}
