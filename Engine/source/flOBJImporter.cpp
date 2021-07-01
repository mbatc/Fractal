#include "flOBJImporter.h"
#include "flMTLImporter.h"
#include "flMath.h"
#include "flSurfaceMaterial.h"
#include "flMesh.h"
#include "flLog.h"
#include "flRef.h"
#include "ctVector.h"
#include "ctFile.h"
#include "ctStringReader.h"

namespace Fractal
{
  class Impl_OBJImporter
  {
  public:
    Impl_OBJImporter() {
      m_pMesh = MakeRef<Mesh>();
    }

    bool ParseVertex(ctVector<ctString> const &tokens) {
      if (tokens.size() >= 4) {
        Vec3D position(0);

        // Position
        for (int64_t i = 1; i < 4; ++i) {
          position[i - 1] = ctScan::Float(tokens[i]);
        }

        m_positions.push_back(position);

        // Colour
        if (tokens.size() == 7) {
          Vec3D colour(0);
          for (int64_t i = 4; i < 7; ++i) {
            colour[i - 4] = ctScan::Float(tokens[i]);
          }

          m_colours.push_back(colour);
        }

        return true;
      }
      else {
        return false;
      }
    }

    bool ParseNormal(ctVector<ctString> const &tokens) {
      if (tokens.size() >= 4) {
        Vec3D normal(0);

        // Position
        for (int64_t i = 1; i < 4; ++i) {
          normal[i - 1] = ctScan::Float(tokens[i]);
        }

        m_normals.push_back(normal);

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

        m_texcoords.push_back(texcoord);

        return true;
      }
      else {
        return false;
      }
    }

    bool ParseFace(ctVector<ctString> const &tokens) {
      if (tokens.size() < 4) {
        return false;
      }

      Polygon polygon;
      polygon.startVertex = m_vertices.size();

      for (int64_t i = 1; i < tokens.size(); ++i) {
        int64_t offset = i - 1;
        Vertex vert;
        ParseFaceIndices(
          tokens[i],
          &vert.pos,
          &vert.tex,
          &vert.nrm
        );

        m_vertices.push_back(vert);
      }

      polygon.endVertex = m_vertices.size() - 1;
      polygon.material = m_activeMaterial;
      m_polygons.push_back(polygon);

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
      ctString mtlName = ReadProperty(line);
      if (mtlName.length() == 0)
        return false;

      m_activeMaterial = ctIndexOf(m_materials.begin(), m_materials.end(), mtlName);
      if (m_activeMaterial == -1) {
        m_activeMaterial = m_materials.size();
        m_materials.push_back(mtlName);
      }

      return true;
    }

    bool Import(char const * filename) {
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

      MTLImporter mtlImporter;
      ctString srcDir = ctFilename(filename).Directory() + "/";
      for (ctString const  & mtlFile : m_mtlFiles) {
        ctFilename mtlPath = ctFile::Find(srcDir + mtlFile);
        mtlImporter.Import(mtlPath.c_str());
      }

      for (ctString const &mtlName : m_materials) {
        SurfaceMaterial * pMaterial = mtlImporter.GetMaterial(mtlName);
        if (pMaterial) {
          m_pMesh->AddMaterial(pMaterial);
        }
        else {
          m_pMesh->AddMaterial(MakeRef(SurfaceMaterial::Create(), false));
        }
      }

      ConstructMesh();

      m_pMesh->SetSourcePath(filename);

      return true;
    }

    void ParseFaceIndices(ctString const & vertex, int64_t *pVert, int64_t *pTexcoord, int64_t *pNormal) {
      char const * pText = vertex.c_str();

      int64_t i   = 0;
      int64_t len = 0;
      int64_t indices[3] = { -1, -1, -1 };

      do {
        indices[i] = ctScan::Int(&pText, &len);
        if (len == 0)
          indices[i] = -1;
        if (*pText == '/')
          pText += 1;
        ++i;
      } while (i < 3 && *pText != 0);

      *pVert     = indices[0];
      *pTexcoord = indices[1];
      *pNormal   = indices[2];
    }

    void ConstructMesh()
    {
      m_pMesh->Clear();

      bool hasColours = m_colours.size() > 0;

      for (int64_t i = 0; i < m_polygons.size(); ++i) {
        Polygon &poly = m_polygons[i];
        int64_t newPolyID = m_pMesh->AddPolygon();

        m_pMesh->SetPolygonMaterial(newPolyID, poly.material);
        for (int64_t v = poly.startVertex; v <= poly.endVertex; ++v) {
          Vertex& vert = m_vertices[v];
          m_pMesh->AddPolygonVertex(
            newPolyID,
            m_pMesh->AddVertex(
              vert.pos != CT_INVALID_INDEX ? m_positions[vert.pos - 1] : Vec3D(0),
              vert.nrm != CT_INVALID_INDEX ? m_normals[vert.nrm - 1]   : Vec3D(0, 1, 0),
              vert.tex != CT_INVALID_INDEX ? m_texcoords[vert.tex - 1] : Vec2D(0),
              hasColours && vert.pos != CT_INVALID_INDEX ? Vec4D(m_colours[vert.pos - 1], 1) : Vec4D(1)
            )
          );
        }
      }
    }

    ctString ReadProperty(const ctString &line) {
      ctStringSeeker seeker(&line);
      seeker.SkipWhitespace();
      seeker.SeekToWhitespace();
      seeker.SkipWhitespace();
      return ctString(seeker.Text()).trim("\"");
    }

    struct Vertex
    {
      int64_t pos;
      int64_t tex;
      int64_t nrm;
    };

    struct Polygon
    {
      int64_t startVertex;
      int64_t endVertex;
      int64_t material;
    };

    Ref<Mesh> m_pMesh = nullptr;

    int64_t m_activeMaterial = -1;

    ctVector<Vec3D> m_positions;
    ctVector<Vec2D> m_texcoords;
    ctVector<Vec3D> m_normals;
    ctVector<Vec3D> m_colours;

    ctVector<Vertex> m_vertices;
    ctVector<Polygon> m_polygons;

    ctVector<ctString> m_mtlFiles;
    ctVector<ctString> m_materials;
  };

  flPIMPL_IMPL(OBJImporter);

  bool OBJImporter::Import(flIN char const * filename) {
    return Impl()->Import(filename);
  }

  Mesh * OBJImporter::GetResult() {
    return Impl()->m_pMesh;
  }
}

