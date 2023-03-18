#pragma once

#include <string>
#include <vector>

class Map
{
  public:
    Map();
    Map(std::string mapName);
    Map(std::string mapName, int sizeX, int sizeY);
    ~Map();

    int MapSizeX;
    int MapSizeY;

    std::string MapName;
    std::vector<std::string> Layers;
    
    static void AddLayer(Map* mMap, std::string layerName);

    static void LoadMapLayer(Map* mMap, std::string layerName);

    static void LoadMap(Map* mMap);

  private:
};

