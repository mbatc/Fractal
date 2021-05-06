#ifndef fl_Graphics_GLProgram_h__
#define fl_Graphics_GLProgram_h__

#include "../flProgram.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLProgram);

    class GLProgram : public Program
    {
      flPIMPL_DEF(GLProgram);

    public:
      static GLProgram* Create();

      void SetShader(flIN const char *source, flIN ProgramStage stage) override;
      void SetShaderFromFile(flIN const char *path, flIN ProgramStage stage) override;
      bool Compile() override;
      bool Reload() override;
      void SetUniformBuffer(flIN const char *name, flIN HardwareBuffer *pBuffer) override;
      void SetTexture(flIN const char *name, flIN Texture *pTexture) override;
      void SetSampler(flIN const char *name, flIN Sampler *pSampler) override;

      void* GetNativeResource() override;
    };
  }
}

#endif // fl_Graphics_Program_h__
