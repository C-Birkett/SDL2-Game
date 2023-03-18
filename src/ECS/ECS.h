#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <map>

//forward declare Component, Entity & Manager classes
class Component;
class Entity;
class Manager;

//ComponentID typedef as size_t
using ComponentID = std::size_t;

//Group typedef as size_t
using Group = std::size_t;

//create new ID for component type
inline ComponentID GetNewComponentTypeID()
{
  static ComponentID lastID = 0u;
  return lastID++;
}

//or return type ID if that component type already exists
template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
  static ComponentID typeID = GetNewComponentTypeID();
  return typeID;
}

//max number of components = 32
constexpr std::size_t maxComponents = 32;

//typedef bitset for components
using ComponentBitSet = std::bitset<maxComponents>;
//array of Component* length maxComponents
using ComponentArray = std::array<Component*, maxComponents>;

//...and for Groups
constexpr std::size_t maxGroups = 32;
using GroupBitSet = std::bitset<maxGroups>;

class Component
{
  public:
    //its owner
    Entity* m_entity;

    virtual ~Component() {}

    //component will contain some data
    //& methods to update, draw etc

    //virtual - will be overriden
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}

};

class Entity
{
  private:
    //its manager
    Manager& m_manager;

    //keep track of alive or dead
    bool active = true;

    //vector of unique_ptr to components
    std::vector<std::unique_ptr<Component>> m_components;

    ComponentArray m_componentArray;
    ComponentBitSet m_componentBitSet;
    GroupBitSet m_groupBitSet;
  
  public:

    Entity(Manager& manager) : m_manager(manager) {}

    void Update()
    {
      //for all components (by reference) of Entity: update
      for(auto& c : m_components) c->Update();
    }
    
    void Draw()
    {
      for(auto& c : m_components) c->Draw();
    }

    bool IsActive() const
    {
      return active;
    }

    void Destroy()
    {
      active = false;
    }

    bool HasGroup(Group mGroup) const noexcept
    {
      return m_groupBitSet[mGroup];
    }

    void AddGroup(Group mGroup);
    void AddGroup(std::string mGroup);

    void DelGroup(Group mGroup) noexcept
    {
      m_groupBitSet[mGroup] = false;
      //manager isnt notified, it'll automatically deal with
      //this during Manager::refresh()
    }

    template <typename T> bool HasComponent() const
    {
      //does componentBitSet match getComponentID for type T
      return m_componentBitSet[GetComponentTypeID<T>()];
    }

    //add components to entity by construction
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... mArgs)
    {
      //check the component doesn't already exist
      assert(!HasComponent<T>());

      //allocate component type T on the heap, by forwarding
      //passed arguments to its constructor
      T* c(new T(std::forward<TArgs>(mArgs)...));

      //set components entity to current instance
      c->m_entity = this;

      //wrap the raw pointer into a smart one for organisation
      //& memory management
      std::unique_ptr<Component> uPtr{c};

      //add the smart pointer to our container with std::move
      m_components.emplace_back(std::move(uPtr));

      //add new component to bitset & array
      m_componentArray[GetComponentTypeID<T>()] = c;
      m_componentBitSet[GetComponentTypeID<T>()] = true;

      //init component after it's added
      c->Init();

      //return reference to newly added component
      return *c;
    }

    template<typename T> T& GetComponent() const
    {
      //retrieve component from the array if it exists
      assert(HasComponent<T>());
      auto ptr(m_componentArray[GetComponentTypeID<T>()]);
      //cast to derived type & dereference
      return *static_cast<T*>(ptr);
    }

    //example use:
    //gameobject.getComponent<PositionComponent>().setXpos(xValue);
};

//if Entity is an aggregate of components,
//the Manager is an aggregate of Entities
class Manager
{
  private:
    //vector of unique_ptr of entities
    std::vector<std::unique_ptr<Entity>> entities;

    //store entities in groups by 'buckets' in this array
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

    //Dictionary to store & manage group names
    std::map<std::string, Group> Groups;
    int numGroups;

  public:

    void Init()
    {
      numGroups = 0;
    }

    void Update()
    {
      for (auto& e : entities) e->Update();
    }

    void Draw()
    {
      for (auto& e : entities) e->Draw();
    }

    //clean up "dead entities" and entities with
    //incorrect groups from their buckets
    void Refresh()
    {
      for(auto i = 0u; i < maxGroups; ++i)
      {
        auto& v(groupedEntities[i]);

        v.erase(
              std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
              {
                return !mEntity->IsActive() || !mEntity->HasGroup(i);
              }),
              std::end(v));
      }

      entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity)
            {
              return !mEntity->IsActive();
            }),
          std::end(entities));
    }

    //add group to Groups dictionary
    void AddGroup(std::string group)
    {
      if (Groups.count(group) == 0)
      {
      Group g = ++numGroups;
      Groups[group] = g;
      }
    }

    Group GetGroup(std::string group)
    {
      if (Groups.count(group) != 0)
      {
        return Groups[group];
      }
      //THIS IS BAD!!!
      else {
      AddGroup(group);
      return Groups[group];
      }
    }

    //add entity to existing group
    void AddToGroup(Entity* mEntity, Group mGroup)
    {
      //should assert that the bucket doesnt already
      //contain mEntity
      groupedEntities[mGroup].emplace_back(mEntity);
    }

    void AddToGroup(Entity* mEntity, std::string mGroup)
    {
      if(Groups.count(mGroup) == 0)
      {
        printf("\nAdding new group: %s", mGroup.c_str());
        this->AddGroup(mGroup);
      }
      //should assert that the bucket doesnt already
      //contain mEntity
      groupedEntities[Groups[mGroup]].emplace_back(mEntity);
    }

    //can get one of the buckets from the array
    std::vector<Entity*>& GetGroupEntities(Group mGroup)
    {
      return groupedEntities[mGroup];
    }

    std::vector<Entity*>& GetGroupEntities(std::string mGroup)
    {
      return groupedEntities[this->GetGroup(mGroup)];
    }

    Entity& AddEntity()
    {
      Entity* e = new Entity(*this);
      std::unique_ptr<Entity> uPtr {e};
      entities.emplace_back(std::move(uPtr));

      return *e;
    }
};
