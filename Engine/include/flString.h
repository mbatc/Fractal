#pragma once

#include "flConfig.h"
#include <codecvt>
#include <locale>

namespace Fractal
{
  inline std::wstring StringToWide(std::string const& str)
  {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(str);
  }

  inline std::string WideToString(std::wstring const& wstr)
  {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(wstr);
  }
}