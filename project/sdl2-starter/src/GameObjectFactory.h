

#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include "GameObject.h"

using namespace std;

class BaseCreator 
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};


class GameObjectFactory 
{
private:
    map<string, BaseCreator*> m_creators;
public:
    bool registerType(string typeID, BaseCreator* pCreator) 
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

    GameObject* create(string typeID) 
    {
        map<string, BaseCreator*>::iterator it = m_creators.find(typeID);
        // check if type already exist
        if(it == m_creators.end()) 
        {
            cout << "type does not exist: " << typeID << endl;
            return NULL;
        }

        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }
};


#endif // define __GameObjectFactory__