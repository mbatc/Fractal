#include "..\include\flSurfaceMaterial.h"
#include "flSurfaceMaterial.h"
#include "ctString.h"

template<typename T>
class StringMap
{
public:
  int64_t Find(ctString const & key) const {
    for (int64_t i = 0; i < m_names.size(); ++i) {
      if (m_names[i] == key) {
        return i;
      }
    }

    return CT_INVALID_INDEX;
  }

  bool Add(ctString const & key, T const & value) {
    if (Find(key) != CT_INVALID_INDEX) {
      return false;
    }

    _Add(key, value);
  }

  void AddOrSet(ctString const &key, T const &value) {
    T *pValue = TryGet(key);
    if (pValue) {
      *pValue = value;
      return;
    }

    _Add(key, value);
  }

  T GetValueOr(ctString const & key, T const & defaultValue) const {
    T const * pValue = TryGet(key);
    return pValue ? *pValue : defaultValue;
  }

  bool Contains(ctString const & key) const {
    return Find(key) != CT_INVALID_INDEX;
  }

  T *       TryGet(ctString const &key)       { return TryGet(Find(key)); }
  T const * TryGet(ctString const &key) const { return TryGet(Find(key)); }

  T *       TryGet(int64_t const &index)       { return index < 0 || index >= size() ? nullptr : &m_values[index]; }
  T const * TryGet(int64_t const &index) const { return index < 0 || index >= size() ? nullptr : &m_values[index]; }

  T &       Get(ctString const &key)       { return Get(Find(key)); }
  T const & Get(ctString const &key) const { return Get(Find(key)); }
  
  T &       Get(int64_t const &index)       { return m_values[index]; }
  T const & Get(int64_t const &index) const { return m_values[index]; }

  int64_t size() const { return m_values.size(); }

  ctVector<T> const &GetValues() const { return m_values; }
  ctVector<ctString> const &GetKeys() const { return m_names; }

protected:
  void _Add(ctString const &key, T const &value) {
    m_names.push_back(key);
    m_values.push_back(value);
  }

  ctVector<T>        m_values;
  ctVector<ctString> m_names;
};

namespace flEngine
{
  class Impl_SurfaceMaterial
  {
  public:
    ctString m_name = "Default";

    StringMap<float>        m_values;
    StringMap<ctString>     m_textures;
    StringMap<Util::Colour> m_colours;
  };

  flPIMPL_IMPL(SurfaceMaterial);

  SurfaceMaterial *SurfaceMaterial::Create()
  {
    return flNew SurfaceMaterial;
  }

  char const *SurfaceMaterial::GetName() const {
    return Impl()->m_name.c_str();
  }

  void SurfaceMaterial::SetName(flIN char const *name) {
    Impl()->m_name = name;
  }

  float SurfaceMaterial::GetValue(flIN char const *name) const {
    return Impl()->m_values.GetValueOr(name, 0.0f);
  }

  Util::Colour SurfaceMaterial::GetColour(flIN char const *name) const {
    return Impl()->m_colours.GetValueOr(name, Util::ColourU32_White);
  }

  char const * SurfaceMaterial::GetTexture(flIN char const *name) const {
    ctString const * pTexPath = Impl()->m_textures.TryGet(name);
    return pTexPath ? pTexPath->c_str() : "";
  }

  void SurfaceMaterial::SetValue(flIN char const *name, flIN float value) {
    Impl()->m_values.AddOrSet(name, value);
  }

  void SurfaceMaterial::SetColour(flIN char const *name, flIN Util::Colour colour) {
    Impl()->m_colours.AddOrSet(name, colour);
  }

  void SurfaceMaterial::SetTexture(flIN char const *name, flIN char const *path) {
    Impl()->m_textures.AddOrSet(name, path);
  }

  int64_t SurfaceMaterial::GetValueCount() const {
    return Impl()->m_values.size();
  }

  int64_t SurfaceMaterial::GetColourCount() const {
    return Impl()->m_colours.size();
  }

  int64_t SurfaceMaterial::GetTextureCount() const {
    return Impl()->m_textures.size();
  }
}