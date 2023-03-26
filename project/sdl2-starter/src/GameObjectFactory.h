

#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include "GameObject.h"

class GameObject;

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
    GameObjectFactory() {}
    ~GameObjectFactory() {}
    static GameObjectFactory* instance;
    map<string, BaseCreator*> m_creators;

public:
    static GameObjectFactory* Instance()
    {
        if(instance == 0)
        {
            instance = new GameObjectFactory();
            return instance;
        }
        return instance;
    }
    bool registerType(string typeID, BaseCreator* pCreator);
    GameObject* create(string typeID);
};

typedef GameObjectFactory _GameObjectFactory;
#endif // define __GameObjectFactory__