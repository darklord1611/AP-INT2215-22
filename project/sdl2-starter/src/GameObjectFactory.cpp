#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::instance = 0;

bool GameObjectFactory::registerType(string typeID, BaseCreator* pCreator)
{
    map<string, BaseCreator*>::iterator it = m_creators.find(typeID);
    // check if type already exist
    if(it != m_creators.end()) 
    {
        delete pCreator;
        return false;
    }
    m_creators[typeID] = pCreator;
    return true;
}

GameObject* GameObjectFactory::create(string typeID) 
{
    map<string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end()) 
    {
        cout << "type " << typeID << " does not exist" << endl;
        return NULL;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject(); 
}




