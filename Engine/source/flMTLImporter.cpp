#include "flMTLImporter.h"
#include "flColour.h"
#include "flMath.h"
#include "flSurfaceMaterial.h"
#include "flRef.h"
#include "flLog.h"

#include "ctVector.h"
#include "ctString.h"
#include "ctFile.h"

static void _Read(ctString const& str, float* pValue) { *pValue = (float)ctScan::Float(str); }
static void _Read(ctString const& str, double* pValue) { *pValue = ctScan::Float(str); }
static void _Read(ctString const& str, int64_t* pValue) { *pValue = ctScan::Int(str); }
static void _Read(ctString const& str, bool* pValue) { *pValue = ctScan::Bool(str); }

template<typename Vec> bool _ReadVec(ctVector<ctString> const& tokens, int64_t start, Vec* pVec)
{
  for (int64_t i = 0; i < Vec::ElementCount; ++i)
  {
    if (start + i >= tokens.size())
      return false;
    _Read(tokens[start + i], &(*pVec)[i]);
  }
  return true;
}

namespace Fractal
{
  class Impl_MTLImporter
  {
  public:
    bool Import(const ctString& path)
    {
      ctString contents = "";
      pActiveMat = nullptr;
      {
        // Read the file text
        ctFile file;
        if (!file.Open(path, atFM_Read))
        {
          flError("Could not open file '%s'", path.c_str());
          return false;
        }

        contents = file.ReadText();

        if (contents.length() == 0)
        {
          flError("'%s' is an empty file", path.c_str());
          return false;
        }
      }

      int64_t lineNum = 0;
      for (ctString const& line : contents.split("\r\n", true))
      {
        ++lineNum;
        ctVector<ctString> tokens = line.split(ctString::Whitespace(), true);
        if (tokens.size() < 2)
          continue;

        ctString& prop = tokens[0];

        // Ignore comments
        if (prop == "#")
        {
          continue;
        }

        if (prop == "newmtl")
        {
          ctString matName = ReadProperty(line);

          if (matName.length() == 0)
          {
            flError("ln %lld: Cannot add new material. No name specified.", lineNum);
          }

          pActiveMat = GetMaterial(matName);
          continue;
        }

        if (pActiveMat == nullptr)
        {
          flWarning("ln %lld: Cannot read material property ('%s'). No active material.", lineNum, prop.c_str());
          continue;
        }

        // Properties
        if (prop.compare("Ka", atSCO_None))
        {
          ReadColour(tokens, MaterialProperty::Phong::ambient);
        }
        else if (prop.compare("Kd", atSCO_None))
        {
          ReadColour(tokens, MaterialProperty::Phong::diffuse);
        }
        else if (prop.compare("Ks", atSCO_None))
        {
          ReadColour(tokens, MaterialProperty::Phong::specular);
        }
        else if (prop.compare("d", atSCO_None))
        {
          ReadValue(tokens, MaterialProperty::Phong::alpha);
        }
        else if (prop.compare("Ns", atSCO_None))
        {
          ReadValue(tokens, MaterialProperty::Phong::specularPower);
        }
        else if (prop.compare("Tr", atSCO_None))
        {
          ReadValue(tokens, MaterialProperty::Phong::alpha);
          pActiveMat->SetValue(MaterialProperty::Phong::alpha, 1 - pActiveMat->GetValue(MaterialProperty::Phong::alpha));
        }
        else if (prop.compare("Ni", atSCO_None))
        {
          ReadValue(tokens, "ior");
        }
        else if (prop.compare("Pr", atSCO_None))
        {
          ReadValue(tokens, MaterialProperty::PBR::roughness);
        }
        else if (prop.compare("Pm", atSCO_None))
        {
          ReadValue(tokens, MaterialProperty::PBR::metalness);
        }
        else if (prop.compare("Ps", atSCO_None))
        {
          ReadValue(tokens, "sheen");
        }
        else if (prop.compare("Ke", atSCO_None))
        {
          ReadColour(tokens, MaterialProperty::PBR::emissive);
        }
        // Maps
        else if (prop.compare("map_Ka", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::Phong::ambient);
        }
        else if (prop.compare("map_Kd", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::Phong::diffuse);
        }
        else if (prop.compare("map_Ks", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::Phong::specular);
        }
        else if (prop.compare("map_d", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::Phong::alpha);
        }
        else if (prop.compare("map_bump", atSCO_None) || prop.compare("bump", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::Phong::normal);
        }
        else if (prop.compare("map_Disp", atSCO_None) || prop.compare("disp", atSCO_None))
        {
          ReadTexture(line, "displacement");
        }
        else if (prop.compare("norm", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::PBR::normal);
        }
        else if (prop.compare("map_Pr", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::PBR::roughness);
        }
        else if (prop.compare("map_Pm", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::PBR::metalness);
        }
        else if (prop.compare("map_Ps", atSCO_None))
        {
          ReadTexture(line, "sheen");
        }
        else if (prop.compare("map_Ke", atSCO_None))
        {
          ReadTexture(line, MaterialProperty::PBR::emissive);
        }
        // else if (prop.compare("map_RMA", atSCO_None)) {
        //   ReadTexture(line, "roughness");
        //   ReadTexture(line, "metalness");
        //   ReadTexture(line, "ambient-occlusion");
        // }
        else
        {
          flWarning("ln %lld: Unsupported material property '%s'.", lineNum, prop.c_str());
        }
      }

      return true;
    }

    bool ReadColour(ctVector<ctString> const& tokens, char const* materialColourName)
    {
      Vec3D colour;
      if (!_ReadVec(tokens, 1, &colour))
      {
        return false;
      }

      pActiveMat->SetColour(materialColourName, Colour(colour));
      return true;
    }

    bool ReadValue(ctVector<ctString> const& tokens, char const* materialValueName)
    {
      if (tokens.size() < 2)
      {
        return false;
      }

      float value;
      _Read(tokens[1], &value);
      pActiveMat->SetValue(materialValueName, value);
      return true;
    }

    bool ReadTexture(ctString const& line, char const* materialTextureName)
    {
      ctString texPath = ReadProperty(line);
      if (texPath.length() == 0)
      {
        return false;
      }

      pActiveMat->SetTexture(materialTextureName, texPath.c_str());
      return true;
    }

    ctString ReadProperty(ctString const& line)
    {
      ctStringSeeker seeker(&line);
      seeker.SkipWhitespace();
      seeker.SeekToWhitespace();
      seeker.SkipWhitespace();

      ctString token = seeker.Text();
      while (token.starts_with("-"))
      {
        seeker.SeekToWhitespace();
        seeker.SkipWhitespace();
        seeker.SeekToWhitespace();
        seeker.SkipWhitespace();
        token = seeker.Text();
      }

      return token.trim("\"");
    }

    Ref<SurfaceMaterial> GetMaterial(ctString const& name)
    {
      for (auto pMaterial : materials)
      {
        if (pMaterial->GetName() == name)
        {
          return pMaterial;
        }
      }

      materials.push_back(MakeRef<SurfaceMaterial>());
      materials.back()->SetName(name.c_str());
      return materials.back();
    }

    Ref<SurfaceMaterial> pActiveMat;

    ctVector<Ref<SurfaceMaterial>> materials;
  };

  flPIMPL_IMPL(MTLImporter);

  MTLImporter* MTLImporter::Create()
  {
    return flNew MTLImporter;
  }

  bool MTLImporter::Import(flIN char const* path)
  {
    return Impl()->Import(path);
  }

  int64_t MTLImporter::GetMaterialCount()
  {
    return Impl()->materials.size();
  }

  SurfaceMaterial* MTLImporter::GetMaterial(flIN char const* name)
  {
    for (Ref<SurfaceMaterial>& mtl : Impl()->materials)
    {
      if (strcmp(mtl->GetName(), name) == 0)
      {
        return mtl.Get();
      }
    }

    return nullptr;
  }

  SurfaceMaterial* MTLImporter::GetMaterial(flIN int64_t index)
  {
    return index < 0 || index >= GetMaterialCount() ? nullptr : Impl()->materials[index].Get();
  }
}
