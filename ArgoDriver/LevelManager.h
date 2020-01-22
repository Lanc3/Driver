#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "rapidjson\rapidjson.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\reader.h"
#include "rapidjson\document.h"
#include "MapObject.h"
#include "Camera.h"
#include "Quad.h"

#include "SAT\CollisionManager.h"

#include "Entity.h"

using namespace std;
class LevelManager
{
public:
	LevelManager();
	~LevelManager();
	void Update(float dt);
	void Draw(Camera* cam, Shader shader);
	glm::vec3 GetCameraStartPosition();
	vector<MapObject*> GetMapObjects();
	int offsetX, offsetY;
	vector<glm::vec3> listOfCheckpoints;
	vector<glm::vec3> listOfCarPoints;
	vector<glm::vec3> listOfCarPointsOther;
	vector<Polygon*> listOfPolygons;
	vector<glm::vec3> listOfRoadPositions;
private :
	FILE* _file;
	vector<MapObject*> m_MapObjectList;
	glm::vec3 m_CameraStartingPosition;
	vector<Quad*> m_TileList;
	vector<pair<string, int>> m_terrainList;
	vector<int> data;
	int m_height, m_width, m_halfTileWidth, m_halfTileHeight, m_tileWidth, m_tileHeight;
	CollisionManager m_collisionManager;	
};

