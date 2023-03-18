#include "Map.h"

#include "Game/Game.h"
#include "ECS/SpriteComponent.h"

#include <cstring>
#include <fstream>
#include <cstdlib>
#include <sstream>

Map::Map()
{
}

Map::Map(std::string mapName)
{
  this->MapName = mapName;
}

Map::Map(std::string mapName, int sizeX, int sizeY){
  this->MapName = mapName;
  this->MapSizeX = sizeX;
  this->MapSizeY = sizeY;
}

Map::~Map()
{
}

//filename convention:
//
//MapName_LayerName_LayerNumber
//
//eg:
//Map1_Terrain_3

void Map::AddLayer(Map* mMap, std::string layerName)
{
  mMap->Layers.emplace_back(layerName);
}

void Map::LoadMapLayer(Map* mMap, std::string layerName)
{
  std::string mapName = mMap->MapName;
  int sizeX = mMap->MapSizeX;
  int sizeY = mMap->MapSizeY;

  std::string pathStr = "./Map/";
  pathStr.append(mapName);
  pathStr.append("_");
  pathStr.append(layerName);
  pathStr.append(".csv");

  printf("\nmap path string set: %s", pathStr.c_str());
  
  TileSet tileSet;
  tileSet.name = layerName;

  std::string tSetStr = "./Map/";
  tSetStr.append(layerName);
  tSetStr.append("_tileset.png");

  tileSet.path = tSetStr.c_str();
  printf("\ntileset path string set: %s", tileSet.path);

  printf("\nopening mapfile: %s", pathStr.c_str());

  std::fstream mapFile;
  mapFile.open(pathStr.c_str());

  int lineNum = 0, xPos = 0, yPos = 0;

  while (mapFile.good())
  {
    std::string line;
    if(lineNum % 50 == 49)
    {
      std::getline(mapFile, line);
    }
    else{
      std::getline(mapFile, line, ',');
    }
    xPos = lineNum % sizeX;
    yPos = static_cast<int>(floor(static_cast<float>(lineNum / sizeX)));
    if(atoi(line.c_str()) != -1)
    {
      //printf("\nadding new %s tile (%s) with ID: %i\nat position: %i, %i", tileSet.name.c_str(), tileSet.path, atoi(line.c_str()), xPos*16, yPos*16);
      Game::AddTile(xPos * 16, yPos * 16, &tileSet, atoi(line.c_str()));
    }
    lineNum++;
  }

  lineNum = 0;

  printf("\nfinished loading mapfile: %s", pathStr.c_str());
  mapFile.close();
}

void Map::LoadMap(Map* mMap)
{
  printf("\nMap: loading map '%s'", mMap->MapName.c_str());

  for(auto& layer : mMap->Layers)
  {
    printf("\nMap: loading map layer: %s", layer.c_str());
    mMap->LoadMapLayer(mMap, layer);
  }
  printf("\nMap: Map '%s' loaded", mMap->MapName.c_str());
}
