#include "LevelManager.h"

using namespace rapidjson;

LevelManager::LevelManager()
{
	_file = new FILE();
	fopen_s(&_file, "LevelData/grassLevel.json", "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream _is(_file, readBuffer, sizeof(readBuffer));
	rapidjson::Document _document;
	_document.ParseStream(_is);
	fclose(_file);
	
	//build out terrain list
	for (const auto& itr : _document["tilesets"].GetArray())
	{
		for (const auto& itrs : itr["terrains"].GetArray())
		{
			m_terrainList.push_back(pair<string, int>(itrs["name"].GetString(), itrs["tile"].GetInt()));
		}
		m_tileWidth = itr["tilewidth"].GetInt();
		m_tileHeight = itr["tileheight"].GetInt();
	}
	m_halfTileHeight = m_tileHeight / 2;
	m_halfTileWidth = m_tileWidth / 2;
	//build out the level tile data
	for (int i = 0; i < _document["layers"][0]["data"].GetArray().Size(); i++)
	{
		data.push_back(_document["layers"][0]["data"][i].GetInt() - 1);
	}
	//build out the models on the map
	for (const auto& itr : _document["layers"].GetArray())
	{
		m_width = itr["width"].GetInt();
		m_height = itr["height"].GetInt();
		
		string layerName = itr["name"].GetString();
		if (layerName == "mapObjects")
		{
			for (const auto& itrs : itr["objects"].GetArray())
			{
				m_MapObjectList.push_back(new MapObject(itrs["x"].GetDouble(), itrs["y"].GetDouble(), itrs["width"].GetDouble(), itrs["height"].GetDouble(), itrs["rotation"].GetDouble(), itrs["type"].GetString(),  glm::vec3(0.6f, 0.6f, 0.6f),true));
			}
		}
		else if (layerName == "camera")
		{
			for (const auto& itrs : itr["objects"].GetArray())
			{
				m_CameraStartingPosition = glm::vec3(itrs["x"].GetDouble(), 4, itrs["y"].GetDouble());
			}
		}
		else if (layerName == "checkpoints")
		{
			for (const auto& itrs : itr["objects"].GetArray())
			{
				offsetX = itrs["x"].GetDouble();
				offsetY = itrs["y"].GetDouble();
				for (const auto& polyItr : itrs["polyline"].GetArray())
				{
					listOfCheckpoints.push_back(glm::vec3(offsetX + polyItr["x"].GetDouble(), 0, offsetY + polyItr["y"].GetDouble()));
				}
			}
		}
		else if (layerName == "civilian")
		{
			for (const auto& itrs : itr["objects"].GetArray())
			{
				
				string layerName = itrs["name"].GetString();
				if (layerName == "t1")
				{
					offsetX = itrs["x"].GetDouble();
					offsetY = itrs["y"].GetDouble();
					for (const auto& polyItr : itrs["polyline"].GetArray())
					{
						listOfCarPoints.push_back(glm::vec3(offsetX + polyItr["x"].GetDouble(), 0, offsetY + polyItr["y"].GetDouble()));
					}//listOfCarPointsOther
				}
				if (layerName == "t2")
				{
					offsetX = itrs["x"].GetDouble();
					offsetY = itrs["y"].GetDouble();
					for (const auto& polyItr : itrs["polyline"].GetArray())
					{
						listOfCarPointsOther.push_back(glm::vec3(offsetX + polyItr["x"].GetDouble(), 0, offsetY + polyItr["y"].GetDouble()));
					}//
				}
			}
		}
		else if (layerName == "collisionPolys")
		{
			for (const auto& itrs : itr["objects"].GetArray())
			{
				offsetX = itrs["x"].GetDouble();
				offsetY = itrs["y"].GetDouble();
				vector<glm::vec2*> m_bounds;
				for (const auto& polyItr : itrs["polygon"].GetArray())
				{
					
					
					m_bounds.push_back(new glm::vec2(polyItr["x"].GetFloat(), polyItr["y"].GetFloat()));
					
				}
				listOfPolygons.push_back(new Polygon(m_bounds, glm::vec3(itrs["x"].GetDouble(), 0, itrs["y"].GetDouble())));
			}
		}
	}
	
	m_halfTileWidth = 64;
	m_halfTileHeight = 64;
	m_tileWidth = 128;
	m_tileHeight = 128;
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			int i = data.at((11 * y) + x);
			string textureName;
			if (i == 20)
			{
				textureName = "leftRight";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(90.0f), "straight", glm::vec3(14, 8,8), false));
				listOfRoadPositions.push_back(glm::vec3(m_halfTileWidth + (x*m_tileWidth), 0.f, m_halfTileHeight + (y*m_tileHeight)));
			}
			else if (i == 21)
			{
				textureName = "upDown";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(0.0f), "straight", glm::vec3(14,8,8),false));
				listOfRoadPositions.push_back(glm::vec3(m_halfTileWidth + (x*m_tileWidth), 0.f, m_halfTileHeight + (y*m_tileHeight)));

			}
			else if (i == 22)
			{
				textureName = "turndown";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(180.0f), "corner", glm::vec3(14, 7.5f, 14), false));
			}
			else if (i == 23)
			{
				textureName = "container";
			}
			else if (i == 15)
			{
				textureName = "opUp";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(0.0f), "corner", glm::vec3(14, 7.5f, 14), false));
			}
			else if (i == 16)
			{
				textureName = "turnUp";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(90.0f), "corner", glm::vec3(14, 7.5f, 14), false));
			}
			else if (i == 17)
			{
				textureName = "opDown";
				m_MapObjectList.push_back(new MapObject(m_halfTileWidth + (x*m_tileWidth), m_halfTileHeight + (y*m_tileHeight), 0, 0, glm::radians(-90.0f), "corner", glm::vec3(14, 7.5f, 14), false));
			}
			else
			{
				textureName = "container";
			}
			m_TileList.push_back(new Quad(glm::vec3(m_halfTileWidth + (x*m_tileWidth), 0, m_halfTileHeight + (y*m_tileHeight)), textureName));
		}
	}


}


LevelManager::~LevelManager()
{
}

void LevelManager::Update(float dt)
{
	for (const auto& itr : m_MapObjectList)
	{
		itr->Update(dt);
	}
}

void LevelManager::Draw(Camera* cam, Shader shader)
{
	for (const auto& itr : m_TileList)
	{
		itr->Draw(cam, shader);
	}

	shader.Use();
	for (const auto& itr : m_MapObjectList)
	{
		itr->Draw(cam, shader);
	}	
}

glm::vec3 LevelManager::GetCameraStartPosition()
{
	return m_CameraStartingPosition;
}

vector<MapObject*> LevelManager::GetMapObjects()
{
	return m_MapObjectList;
}
