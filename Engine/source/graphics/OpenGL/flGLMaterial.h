#ifndef flGLMaterial_h__
#define flGLMaterial_h__

#include "graphics/flMaterial.h"
#include "ctHashMap.h"
#include "ctString.h"
#include "flRef.h"

namespace flEngine
{
  namespace Util { enum Type; }

  namespace Graphics
  {
    enum  TextureType;
    class Texture;
    class UniformBuffer;

    class GLMaterial : public Material
    {
    public:
      static Material* Create(Program * pProgram);

      virtual void Bind() override;
      virtual bool SetValue(char const* name, float value) override;
      virtual bool SetValue(char const* name, float const* pValues, int64_t componentCount) override;
      virtual bool SetTexture(char const* name) override;

    private:
      struct ValueData
      {
        Util::Type type;
        int64_t    width;
        void*      pOffset;
      };

      struct TextureData
      {
        uint32_t     textureUnit;
        TextureType  textureType;
        Ref<Texture> texture;
      };

      ctHashMap<ctString, ValueData>   m_values;
      ctHashMap<ctString, TextureData> m_textures;

      ctVector<uint8_t> m_shaderData;
      ctVector<uint8_t> m_activeShaderData;
      Ref<UniformBuffer> m_uniformBuffer;
    };
  }
}

#endif // flGLMaterial_h__
