#pragma once

#include "flConfig.h"

#include <windows.h>
#include <ctString.h>
#include <shobjidl_core.h>

namespace Fractal
{
  namespace SystemDialog
  {
    class Impl_OpenFile
    {
    public:
      void Construct(bool openFolder, bool multiselect);
      bool Show(char const* initialPath);
      void SetFilter(char const** pExtensions, char const** pDescriptions, int64_t count);
      int64_t GetSelectedCount() const;
      char const* GetSelected(int64_t index) const;

    private:
#if flUSING(flPLATFORM_WINDOWS)
      IFileOpenDialog* m_pSystemDialog = nullptr;
#endif
      ctVector<ctString> m_selected;
    };
  }
}
