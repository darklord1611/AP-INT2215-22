#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

/* 
Parsing routine

1. Load the XML file.

2. Get the root element, <ROOT>.

3. Get the first child of the root element, <ELEMENTS>.

4. For each child, <ELEMENT> of <ELEMENTS>, get the content.

5. Close the file. 
*/

bool StateParser::parseState(string fileName, string stateID, vector<GameObject*> *pObjects, vector<string> *pTextureIDs)
{
	//create the XML document
	TiXmlDocument xmlDoc;
	//load the state file
	if (!xmlDoc.LoadFile(fileName.c_str()))
	{
		cerr << xmlDoc.ErrorDesc() << " 123" << endl;
		return false;
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement(); // <STATES>

	//pre declare the states root node
	TiXmlElement* pStateRoot = 0;
	//get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}

	//pre declare the texture root
	TiXmlElement* pTextureRoot = 0;

	//get the root of the textre elements
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	//now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);

	//pre declare the object root node
	TiXmlElement* pObjectRoot = 0;

	//get the root node and assign it to pObjectRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	//now parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, vector<string> *pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		string filenameAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);

		_TextureManager::Instance()->load(filenameAttribute, idAttribute, theGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement* pStateRoot, vector<GameObject*> *pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		
		textureID = e->Attribute("textureID");

		GameObject* pGameObject = _GameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
		pObjects->push_back(pGameObject);
	}
}