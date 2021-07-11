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
  SceneMeshImporter* SceneMeshImporter::Create()
  {
    return flNew SceneMeshImporter;
  }

  bool SceneMeshImporter::Import(Node* pNode, char const* filepath, void* pUserData)
  {
    OBJImporter meshImporter;
    if (!meshImporter.Import(filepath))
      return false;

    API* pGraphics = GetGraphicsAPI();

    Ref<Program> pProgram;

    // TODO: Load a shader based on the material
    Ref<Task> pProgramLoadTask = MakeRef(Application::EnqueueTask(MakeTask([&]()
    {
      pProgram = MakeRef(pGraphics->CreateProgram(), false);
      pProgram->SetShaderFromFile("../../Engine/assets/shader-library/lighting.frag", ProgramStage_Fragment);
      pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", ProgramStage_Vertex);
      pProgram->Compile();
      return 0;
    })), true);

    Ref<Mesh> pMesh = MakeRef(meshImporter.GetResult(), true);
    pMesh->Triangulate();

    Ref<RenderMesh>   pRenderMesh;
    Application::Await(MakeTask([&]() { pRenderMesh = MakeRef<RenderMesh>(pGraphics, pMesh); return 0; }));

    Ref<MeshRenderer> pRenderer = pNode->AddComponent<MeshRenderer>();

    pRenderer->SetMesh(pRenderMesh);

    pProgramLoadTask->Await(); // Wait for the program to compile

    ctVector<Ref<Task>> loadTasks;

    for (int64_t materialIndex = 0; materialIndex < pMesh->GetMaterialCount(); ++materialIndex)
    {
      SurfaceMaterial* pMaterialData = pMesh->GetMaterial(materialIndex);
      Ref<ShaderMaterial> pShaderMaterial;
      Application::Await(MakeTask([&]()
      {
        pShaderMaterial = MakeRef(pGraphics->CreateMaterial(pProgram), false);
        return 0;
      }));

      // Set textures
      for (int64_t textureIndex = 0; textureIndex < pMaterialData->GetTextureCount(); ++textureIndex)
      {
        bool found = false;
        ctString texturePath = pMaterialData->GetTexture(textureIndex);
        ctFilename fullPath = ctFile::Find(ctString(pMesh->GetSourceDirectory()) + "/" + texturePath, &found);
        if (found)
        {
          // Load the texture
          Ref<Image> pImage = MakeRef<Image>(fullPath.c_str());

          Ref<Texture2D> pTexture;
          Application::Await(MakeTask([&]()
          {
            pTexture = MakeRef(pGraphics->CreateTexture2D(PixelFormat_RGBA, PixelComponentType_UNorm8), false);
            return 0;
          }));

          pShaderMaterial->SetTexture(
            ShaderInput::TextureName(pMaterialData->GetTextureName(textureIndex)).c_str(),
            pTexture
          );

          loadTasks.push_back(MakeRef(Application::EnqueueTask(MakeTask([ = ]()
          {
            pTexture->SetFromImage(pImage);
            pTexture->GenerateMipMaps();
            return 0;
          })), true));
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

      loadTasks.push_back(MakeRef(Application::EnqueueTask(MakeTask([ = ]() mutable { pShaderMaterial->Apply(); return 0; })), true));

      // Add shader and material to the renderer
      pRenderer->SetMaterial(materialIndex, pShaderMaterial);
      pRenderer->SetShader(materialIndex, pProgram);
    }

    // Await tasks to be executed on the main thread
    for (auto& pTask : loadTasks)
      pTask->Await();

    return true;
  }
}
