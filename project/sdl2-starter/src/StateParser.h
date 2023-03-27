#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include <tinyxml2/tinyxml.h>
#include "GameObject.h"


using namespace std;

class GameObject;

class StateParser
{
private:
    void parseObjects(TiXmlElement* pStateRoot, vector<GameObject*> *pObjects);
	void parseTextures(TiXmlElement* pStateRoot, vector<string> *pTextureIDs);
public:
	bool parseState(const char* stateFile, string stateID, vector<GameObject*> *pObjects, vector<string> *pTextureIDs);
};

#endif // define __StateParser__