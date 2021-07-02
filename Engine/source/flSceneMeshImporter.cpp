#include "flSceneMeshImporter.h"
#include "flSurfaceMaterial.h"
#include "flShaderMaterial.h"
#include "flMeshRenderer.h"
#include "flOBJImporter.h"
#include "flApplication.h"
#include "flShaderInput.h"
#include "flTexture2D.h"
#include "flProgram.h"
#include "flImage.h"
#include "flMesh.h"
#include "flNode.h"
#include "flAPI.h"

#include "ctFilename.h"
#include "ctFile.h"

namespace Fractal
{
  SceneMeshImporter *SceneMeshImporter::Create()
  {
    return flNew SceneMeshImporter;
  }

  bool SceneMeshImporter::Import(Node *pNode, char const *filepath, void *pUserData)
  {
    OBJImporter meshImporter;
    if (!meshImporter.Import(filepath))
      return false;

    Application &app = Application::Get();
    API *pGraphics = app.GetGraphicsAPI();

    Ref<Mesh> pMesh = MakeRef(meshImporter.GetResult(), true);

    // TODO: Load a shader based on the material
    Ref<Program> pProgram = MakeRef(pGraphics->CreateProgram(), false);
    pProgram->SetShaderFromFile("../../Engine/assets/shader-library/textured.frag", ProgramStage_Fragment);
    pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", ProgramStage_Vertex);
    pProgram->Compile();

    pMesh->Triangulate();

    Ref<RenderMesh>   pRenderMesh = MakeRef<RenderMesh>(pGraphics, pMesh);
    Ref<MeshRenderer> pRenderer = pNode->AddComponent<MeshRenderer>();

    pRenderer->SetMesh(pRenderMesh);

    for (int64_t materialIndex = 0; materialIndex < pMesh->GetMaterialCount(); ++materialIndex)
    {
      SurfaceMaterial *pMaterialData = pMesh->GetMaterial(materialIndex);
      Ref<ShaderMaterial> pShaderMaterial = MakeRef(pGraphics->CreateMaterial(pProgram), false);

      // Set textures
      for (int64_t textureIndex = 0; textureIndex < pMaterialData->GetTextureCount(); ++textureIndex)
      {
        bool found = false;
        ctString texturePath = pMaterialData->GetTexture(textureIndex);
        ctFilename fullPath = ctFile::Find(ctString(pMesh->GetSourceDirectory()) + "/" + texturePath, &found);
        if (found)
        { // Load the texture
          Image image(fullPath.c_str());

          Ref<Texture2D> pTexture = MakeRef(pGraphics->CreateTexture2D(PixelFormat_RGBA, PixelComponentType_UNorm8), false);
          pTexture->SetFromImage(&image);
          pTexture->GenerateMipMaps();

          pShaderMaterial->SetTexture(
            ShaderInput::TextureName(pMaterialData->GetTextureName(textureIndex)).c_str(),
            pTexture
          );
        }
      }

      // Set Colours
      for (int64_t colourIndex = 0; colourIndex < pMaterialData->GetColourCount(); ++colourIndex)
        pShaderMaterial->SetValue(
          ShaderInput::ColourName(pMaterialData->GetColourName(colourIndex)).c_str(),
          pMaterialData->GetColour(colourIndex)
        );

      // Set Values
      for (int64_t valueIndex = 0; valueIndex < pMaterialData->GetValueCount(); ++valueIndex)
        pShaderMaterial->SetValue(
          ShaderInput::ColourName(pMaterialData->GetValueName(valueIndex)).c_str(),
          pMaterialData->GetValue(valueIndex)
        );

      pShaderMaterial->Apply();

      // Add shader and material to the renderer
      pRenderer->SetMaterial(materialIndex, pShaderMaterial);
      pRenderer->SetShader(materialIndex, pProgram);
    }

    return true;
  }
}
