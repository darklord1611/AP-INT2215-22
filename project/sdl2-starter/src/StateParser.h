#ifndef __StateParser__
#define __StateParser__

#include <vector>
#include "tinyxml.h"
#include "GameObject.h"
#include <memory>

using namespace std;


class StateParser
{
private:
    void parseObjects(TiXmlElement* pStateRoot, vector<GameObject*> *pObjects);
	void parseTextures(TiXmlElement* pStateRoot, vector<string> *pTextureIDs);
public:
	bool parseState(string fileName, string stateID, vector<GameObject*> *pObjects, vector<string> *pTextureIDs);
};

#endif // define __StateParser__