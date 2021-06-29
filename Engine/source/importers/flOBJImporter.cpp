#include "importers/flOBJImporter.h"
#include "math/flMath.h"
#include "flMesh.h"
#include "flLog.h"

#include "ctVector.h"
#include "ctFile.h"
#include "ctStringReader.h"

using namespace flEngine;
using namespace flEngine::Math;

template<size_t N>
bool _Compare(char const (&token)[N], char const *str)
{
  return strncmp(str, token, N);
}

template<typename T, size_t N>
bool _ReadValues(T *pValues, ctStringSeeker *pSeeker)
{
  for (int64_t i = 0; i < N; ++i) {
    pSeeker->SkipWhitespace();
    int64_t len;
    pValues[i] = ctScan::Scan<T>(pSeeker->Text(), &len);
    pSeeker->Seek(len);
  }
  return true;
}

namespace flEngine
{
  class Impl_OBJImporter
  {
  public:
    bool ParseVertex(ctVector<ctString> const &tokens) {
      if (tokens.size() >= 4) {
        Vec3D position(0);
        Vec4D colour(0);

        // Position
        for (int64_t i = 1; i < 4; ++i) {
          position[i - 1] = ctScan::Float(tokens[i]);
        }

        // Colour
        if (tokens.size() == 8) {
          for (int64_t i = 4; i < 8; ++i) {
            colour[i - 4] = ctScan::Float(i);
          }
        }

        return true;
      }
      else {
        return false;
      }
    }

    bool ParseNormal(ctVector<ctString> const &tokens) {
      if (tokens.size() >= 4) {
        Vec3D position(0);

        // Position
        for (int64_t i = 1; i < 4; ++i) {
          position[i - 1] = ctScan::Float(tokens[i]);
        }

        return true;
      }
      else {
        return false;
      }
    }

    bool ParseTexcoord(ctVector<ctString> const &tokens) {
      if (tokens.size() > 2) {
        Vec2D texcoord(0);
        for (int64_t i = 1; i < 3; ++i) {
          texcoord[i - 1] = ctScan::Float(tokens[i]);
        }

        return true;
      }
      else {
        return false;
      }
    }

    bool ParseFace(ctVector<ctString> const &tokens) {
      Triangle tri;
      for (int64_t i = 1; i < tokens.size(); ++i) {
        int64_t offset = i - 1;
        ParseFaceIndices(
          tokens[i],
          tri.pos + offset,
          tri.tex + offset,
          tri.nrm + offset
        );
      }

      m_triangle.push_back(tri);
      return true;
    }

    bool ParseMTLLib(const ctString &line) {
      ctString libFile = ReadProperty(line);
      if (libFile.length() == 0)
        return false;

      m_mtlFiles.push_back(libFile);
      return true;
    }

    bool ParseUseMTL(const ctString &line) {
      ctString useMtl = ReadProperty(line);
      if (useMtl.length() == 0)
        return false;

      m_activeMaterial = ctIndexOf(m_materials.begin(), m_materials.end(), useMtl);
      if (m_materials == -1) {
        m_activeMaterial = m_materials.size();
        m_materials.push_back(line);
      }

      return true;
    }

    bool Import(flIN char const *filename) {
      ctFile file;
      if (!file.Open(filename, atFM_Read)) {
        flError("Could not open file '%s'", filename);
        return false;
      }

      ctStringReader reader(&file);

      while (reader.Available() > 0) {
        ctString const &line = reader.ReadLine();
        ctStringSeeker seeker(&line);
        seeker.SkipWhitespace();
        ctVector<ctString> tokens = line.split(ctString::Whitespace(), true);
        if (tokens.size() == 0)
          continue;

        if (tokens[0] == "v") {
          ParseVertex(tokens);
        }
        else if (tokens[0] == "vn") {
          ParseNormal(tokens);
        }
        else if (tokens[0] == "vt") {
          ParseTexcoord(tokens);
        }
        else if (tokens[0] == "f") {
          ParseFace(tokens);
        }
        else if (tokens[0] == "mtllib") {
          ParseMTLLib(line);
        }
        else if (tokens[0] == "usemtl") {
          ParseUseMTL(line);
        }
      }

      return true;
    }

    void ParseFaceIndices(ctString const & vertex, int64_t *pVert, int64_t *pTexcoord, int64_t *pNormal) {
      char const * pText = vertex.c_str();

      int64_t i   = -1;
      int64_t len = 0;
      int64_t indices[3] = { -1, -1, -1 };

      do {
        indices[i] = ctScan::Int(&pText, &len);

        if (len == 0)
          indices[i] = -1;

        pText += len;

        if (*pText == '/')
          pText += 1;

        ++i;
      } while (pText <= vertex.end());

      *pVert     = indices[0];
      *pTexcoord = indices[1];
      *pNormal   = indices[2];
    }

    ctString ReadProperty(const ctString &line) {
      ctStringSeeker seeker(&line);
      seeker.SkipWhitespace();
      seeker.SeekToWhitespace();
      seeker.SkipWhitespace();
      return ctString(seeker.Text()).trim("\"");
    }

    struct Triangle
    {
      int64_t pos[3];
      int64_t tex[3];
      int64_t nrm[3];
    };

    Mesh m_mesh;

    int64_t m_activeMaterial = -1;

    ctVector<Vec3D> position;
    ctVector<Vec2D> texcoord;
    ctVector<Vec3D> normal;

    ctVector<Triangle> m_triangle;
    ctVector<ctString> m_mtlFiles;
    ctVector<ctString> m_materials;
  };

  flPIMPL_IMPL(OBJImporter);

  bool OBJImporter::Import(flIN char const * filename) {
    return Impl()->Import(filename);
  }

  Mesh * OBJImporter::GetResult() {
    return &Impl()->m_mesh;
  }
}

