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
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object layers 
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) 
    { 
        if(e->Value() == std::string("layer")) 
        { 
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets()); 
        } 
    }

    return pLevel;
}
