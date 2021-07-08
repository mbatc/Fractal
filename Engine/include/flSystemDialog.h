#pragma once

#include "flInterface.h"
#include <string>
#include <vector>

namespace Fractal
{
  namespace SystemDialog
  {
    class Impl_OpenFile;

    class flEXPORT OpenFile : public Interface
    {
      flPIMPL_DEF(OpenFile);

    public:
      OpenFile(flIN bool openFolder, flIN bool multiselect);

      bool Show(flIN char const* initialPath);

      void SetFilter(flIN char const** pExtensions, flIN char const** pDescriptions, flIN int64_t count);

      int64_t GetSelectedCount() const;

      char const* GetSelected(int64_t index) const;

      inline void SetFilter(flIN std::initializer_list<std::pair<std::string, std::string>> const& extensions)
      {
        std::vector<char const*> names;
        std::vector<char const*> descriptions;

        for (auto& item : extensions)
        {
          names.push_back(item.first.c_str());
          descriptions.push_back(item.second.c_str());
        }

        SetFilter(names.data(), descriptions.data(), extensions.size());
      }
    };
  }
}