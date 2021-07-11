#include "flComponentRegistry.h"
#include "flComponent.h"
#include "ctString.h"
#include "flLog.h"

namespace Fractal
{
  struct ComponentDetails
  {
    bool     valid = false;
    int64_t  baseID = -1;
    ctString name = "";
    ComponentAllocator   allocator;
    ComponentDeallocator deallocator;
  };

  static ctVector<ComponentDetails> _components =
  {
    { true, -1, Component::Type() }
  };

  static ctVector<ctVector<bool>> _derivedMap;

  static int64_t _nextTypeID = 0;

  bool ComponentRegistry::Register(flIN char const* typeName, flIN int64_t typeID, flIN int64_t baseTypeID, flIN ComponentAllocator allocator, flIN ComponentDeallocator deallocator)
  {
    if (typeID >= _components.size())
      _components.resize(typeID + 1);

    ComponentDetails& info = _components[typeID];
    if (info.valid)
    {
      flError("Cannot register component '%s'. TypeID (%lld) is already used by '%s'.", typeName, typeID, info.name.c_str());
      return false;
    }

    _derivedMap.clear();
    info.name        = typeName;
    info.baseID      = baseTypeID;
    info.allocator   = allocator;
    info.deallocator = deallocator;
    return true;
  }

  bool ComponentRegistry::IsBase(flIN int64_t baseID, flIN int64_t derivedID)
  {
    if (baseID >= ComponentCount() || derivedID >= ComponentCount())
      return false;

    if (_derivedMap.empty())
    {
      // Build class hierarchy lookup
      _derivedMap.resize(ComponentCount());
      for (int64_t i = 0; i < _derivedMap.size(); ++i)
      {
        ctVector<bool>& isBase = _derivedMap[i];
        isBase.resize(ComponentCount(), false);

        int64_t nextBase = _components[i].baseID;
        while (nextBase != -1)
        {
          isBase[nextBase] = true;
          nextBase = _components[nextBase].baseID;
        }
      }
    }

    return _derivedMap[derivedID][baseID];
  }

  int64_t ComponentRegistry::GetBaseTypeID(flIN int64_t derivedID)
  {
    return derivedID >= 0 && derivedID < _components.size() ? _components[derivedID].baseID : -1;
  }

  int64_t ComponentRegistry::ComponentCount()
  {
    return _components.size();
  }

  char const* ComponentRegistry::GetComponentName(flIN int64_t typeID)
  {
    return _components[typeID].name.c_str();
  }

  int64_t ComponentRegistry::GetTypeID(flIN char const * typeName)
  {
    for (int64_t i = 0; i < _components.size(); ++i)
      if (strcmp(_components[i].name, typeName) == 0)
        return i;
    return -1;
  }

  int64_t ComponentRegistry::NextTypeID()
  {
    return ++_nextTypeID;
  }

  Component *ComponentRegistry::Create(flIN int64_t typeID)
  {
    if (_components[typeID].allocator == nullptr)
    {
      flError("Cannot instantiate component '%s'. Allocator is null.", GetComponentName(typeID));
      return nullptr;
    }

    return _components[typeID].allocator();
  }

  void ComponentRegistry::Destroy(Component *pComponent)
  {
    int64_t typeID = pComponent->GetTypeID();
    _components[typeID].deallocator(pComponent);
  }
}
