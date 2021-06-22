#include "scene/flComponentRegistry.h"
#include "scene/flComponent.h"
#include "ctString.h"
#include "flLog.h"

namespace flEngine
{
  namespace Scene
  {
    struct ComponentDetails
    {
      bool     valid  = false;
      int64_t  baseID = -1;
      ctString name   = "";
    };

    static ctVector<ComponentDetails> _components = {
      { true, -1, Component::Type() }
    };

    static ctVector<ctVector<bool>>   _derivedMap;

    static int64_t _nextTypeID = 0;

    bool ComponentRegistry::Register(flIN char const * typeName, flIN int64_t typeID, flIN int64_t baseTypeID)
    {
      if (typeID >= _components.size())
        _components.resize(typeID + 1);

      ComponentDetails &info = _components[typeID];
      if (info.valid)
      {
        flError("Cannot register component '%s'. TypeID (%lld) is already used by '%s'.", typeName, typeID, info.name.c_str());
        return false;
      }

      _derivedMap.clear();
      info.name   = typeName;
      info.baseID = baseTypeID;
      return true;
    }

    bool ComponentRegistry::IsBase(flIN int64_t baseID, flIN int64_t derivedID)
    {
      if (baseID >= ComponentCount() || derivedID >= ComponentCount())
        return false;

      if (_derivedMap.empty())
      { // Build class hierarchy lookup
        _derivedMap.resize(ComponentCount());
        for (int64_t i = 0; i < _derivedMap.size(); ++i)
        {
          ctVector<bool> &isBase = _derivedMap[derivedID];
          isBase.resize(ComponentCount());

          int64_t nextBase = _components[derivedID].baseID;
          while (nextBase != -1)
          {
            _derivedMap[nextBase] = true;
            nextBase = _components[nextBase].baseID;
          }
        }
      }

      return _derivedMap[derivedID][baseID];
    }

    int64_t ComponentRegistry::ComponentCount()
    {
      return _components.size();
    }

    char const * ComponentRegistry::GetComponentName(flIN int64_t typeID)
    {
      return _components[typeID].name.c_str();
    }
    int64_t ComponentRegistry::NextTypeID()
    {
      return ++_nextTypeID;
    }
  }
}
