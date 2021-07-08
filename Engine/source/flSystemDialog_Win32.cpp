#include "flSystemDialog_Impl.h"
#include "flString.h"
#include "flLog.h"

namespace Fractal
{
  namespace SystemDialog
  {
    void Impl_OpenFile::Construct(bool openFolder, bool multiselect)
    {
      HRESULT result = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pSystemDialog));
      if (FAILED(result))
      {
        flError("Failed to create Open File Dialog");
        return;
      }

      FILEOPENDIALOGOPTIONS opts = 0;
      m_pSystemDialog->GetOptions(&opts);
      opts |= (openFolder * FOS_PICKFOLDERS) | FOS_FILEMUSTEXIST | (multiselect * FOS_ALLOWMULTISELECT);
      m_pSystemDialog->SetOptions(opts);
    }

    bool Impl_OpenFile::Show(char const* initialPath)
    {
      initialPath;

      if (m_pSystemDialog == nullptr)
        return false;

      if (FAILED(m_pSystemDialog->Show(nullptr)))
        return false;

      IShellItemArray* pItemArray;
      if (SUCCEEDED(m_pSystemDialog->GetResults(&pItemArray)))
      {
        DWORD count;
        if (SUCCEEDED(pItemArray->GetCount(&count)))
        {
          for (int64_t i = 0; i < count; ++i)
          {
            IShellItem* pItem;
            if (SUCCEEDED(pItemArray->GetItemAt((DWORD)i, &pItem)))
            {
              LPWSTR displayName;
              if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &displayName)))
              {
                m_selected.push_back(WideToString(displayName).c_str());
              }
            }
          }
        }
      }

      return true;
    }

    void Impl_OpenFile::SetFilter(char const** pExtensions, char const** pDescriptions, int64_t count)
    {
      ctVector<COMDLG_FILTERSPEC> filterSpecs(count, {});

      ctVector<std::wstring> names(count, L""); // Store the strings somewhere
      ctVector<std::wstring> patterns(count, L""); // Store the strings somewhere

      for (int64_t i = 0; i < count; ++i)
      {
        // Store strings
        names[i] = StringToWide(pDescriptions[i]);
        patterns[i] = StringToWide(std::string("*.") + pExtensions[i]);

        // Pass filter to WinAPI structure
        filterSpecs[i].pszName = names[i].c_str();
        filterSpecs[i].pszSpec = patterns[i].c_str();
      }

      m_pSystemDialog->SetFileTypes((uint32_t)count, filterSpecs.data());
    }

    int64_t Impl_OpenFile::GetSelectedCount() const
    {
      return m_selected.size();
    }

    char const* Impl_OpenFile::GetSelected(int64_t index) const
    {
      return index < 0 || index >= m_selected.size() ? nullptr : m_selected[index].c_str();
    }
  }
}