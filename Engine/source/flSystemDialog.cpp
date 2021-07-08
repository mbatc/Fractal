#include "flSystemDialog.h"
#include "flSystemDialog_Impl.h"

namespace Fractal
{
  namespace SystemDialog
  {
    flPIMPL_IMPL(OpenFile);

    OpenFile::OpenFile(flIN bool openFolder, flIN bool multiselect)
    {
      Impl()->Construct(openFolder, multiselect);
    }

    bool OpenFile::Show(flIN char const* initialPath)
    {
      return Impl()->Show(initialPath);
    }

    void OpenFile::SetFilter(flIN char const** pExtensions, flIN char const** pDescriptions, flIN int64_t count)
    {
      Impl()->SetFilter(pExtensions, pDescriptions, count);
    }

    int64_t OpenFile::GetSelectedCount() const
    {
      return Impl()->GetSelectedCount();
    }

    char const* OpenFile::GetSelected(int64_t index) const
    {
      return Impl()->GetSelected(index);
    }
  }
}
