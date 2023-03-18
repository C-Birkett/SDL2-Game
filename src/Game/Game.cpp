#include "Game.h"

#include "TextureManager/TextureManager.h"
//#include "GameObject/GameObject.h"
#include "Map/Map.h"
#include "ECS/Components.h"
#include "Vector2D/Vector2D.h"
#include "Collision/Collision.h"

//for tileset class
#include "ECS/SpriteComponent.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

Map* currentMap;


/*
enum groupLabels : std::size_t
{
  groupMap,
  groupPlayers,
  groupEnemies,
  groupColliders,
};
*/


Game::Game(){

}

Game::~Game(){

}

void Game::init(const char *title, int width, int height, bool fullscreen){

  int flags = 0;

  //fullscreen
  if(fullscreen){
    flags = SDL_WINDOW_FULLSCREEN;
  }

  //init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0){

    isRunning = true;
    
    //create game window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window == NULL)
	{
		printf("Failed to open %d x %d window: %s\n", width, height, SDL_GetError());
  }
	
    //game renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(renderer){
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
  }

  manager.AddGroup("groupPlayers");
  player.AddComponent<TransformComponent>(100.0f, 100.0f, 16, 32, 4);
  player.AddComponent<SpriteComponent>("Textures/player.png", true);
  player.AddComponent<KeyboardController>();
  player.AddComponent<ColliderComponent>("player");
  player.AddGroup("groupPlayers");

  manager.AddGroup("groupMap");
  printf("\nGame: initialising map");
  Map testMap("Map", 50, 50);
  testMap.AddLayer(&testMap, static_cast<std::string>("Base"));
  testMap.AddLayer(&testMap, static_cast<std::string>("Dirt"));
  testMap.AddLayer(&testMap, static_cast<std::string>("Grass"));
  
  //printf("\nthere are %lu tiles in Base", manager.getGroupEntities("Base").size());
  //printf("\nthere are %lu tiles in Dirt", manager.getGroupEntities("Dirt").size());
  //printf("\nthere are %lu tiles in Grass", manager.getGroupEntities("Grass").size());

  printf("\nGame: Loading Map...");
  testMap.LoadMap(&testMap);
  currentMap = &testMap;

  wall.AddComponent<TransformComponent>(300.0f, 300.0f, 20, 300, 1);
  wall.AddComponent<SpriteComponent>("./Textures/dirt.png");
  wall.AddComponent<ColliderComponent>("wall");
  wall.AddGroup("groupMap");

  manager.AddGroup("groupEnemies");
}

void Game::handleEvents()
{

  while(SDL_PollEvent(&event))
  {
    switch (event.type){
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
  }
  }
}

void Game::update()
{
  manager.Refresh();
  manager.Update();

  if(Collision::AABB(player.GetComponent<ColliderComponent>().GetCollider(), wall.GetComponent<ColliderComponent>().GetCollider()))
  {
    std::cout << "Wall Hit!" << std::endl;
    //'bounce' against wall
    player.GetComponent<TransformComponent>().velocity * -1;
  }
}

void Game::render(){
  //clear screen
  SDL_SetRenderDrawColor(renderer, 0,0,0,0);
  SDL_RenderClear(renderer);

  //paint algorithm

  auto& tiles(manager.GetGroupEntities("groupMap"));
  auto& players(manager.GetGroupEntities("groupPlayers"));
  auto& enemies(manager.GetGroupEntities("groupEnemies"));

  auto& baseTiles(manager.GetGroupEntities("Base"));
  auto& dirtTiles(manager.GetGroupEntities("Dirt"));
  auto& grassTiles(manager.GetGroupEntities("Grass"));
  
  for(auto& b : baseTiles)
    {
      b->Draw();
    }
  for(auto& d : dirtTiles)
    {
      d->Draw();
    }
  for(auto& g : grassTiles)
    {
      g->Draw();
    }

  /*

  for(auto l = currentMap->Layers.begin(); l != currentMap->Layers.end(); ++l)
  {
    printf("drawing map layer");
    printf("drawing map layer");
    auto& layerTiles(manager.getGroupEntities(*l));
    for(auto& t : layerTiles)
    {
      t->draw();
    }
  }

  */

  /*
  for(auto& t : tiles)
  {
    t->draw();
  }
  */

  for(auto& p : players)
  {
    p->Draw();
  }

  for(auto& e : enemies)
  {
    e->Draw();
  }

  SDL_RenderPresent(renderer);
}

void Game::clean(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::AddTile(int x, int y, TileSet* tileSet, int ID)
{
  auto& tile(manager.AddEntity());
  tile.AddComponent<TileComponent>(x, y, 16, 16, tileSet, ID);
  //printf("\ntile: adding to group '%s'", tileSet->name.c_str());
  tile.AddGroup(tileSet->name);
  //printf("\ntile: adding to group 'groupMap'");
  //tile.addGroup("groupMap");
}
