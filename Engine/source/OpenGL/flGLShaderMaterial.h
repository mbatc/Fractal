#pragma once

#include "flShaderMaterial.h"
#include "ctHashMap.h"
#include "ctString.h"
#include "flRef.h"

namespace Fractal
{
  namespace Util { enum Type; }

    enum  TextureType;
    class Texture;
    class UniformBuffer;

    class GLShaderMaterial : public ShaderMaterial
    {
    public:
      GLShaderMaterial(API *pAPI, Program *pProgram, char const *blockName);

      static ShaderMaterial* Create(API *pAPI, Program * pProgram, char const * blockName = "Material");

      virtual void Apply() override;
      virtual void Bind() override;
      virtual bool SetValue(char const* name, float value) override;
      virtual bool SetValue(char const* name, float const* pValues, int64_t componentCount) override;
      virtual bool SetTexture(char const* name, Texture * pTexture) override;
      virtual bool SetSampler(char const* name, Sampler * pTexture) override;

    private:
      bool SetValue(char const * name, void const * pValue, Type const & type, int64_t const & width);

      struct ValueData
      {
        Type type;
        int64_t    width;
        int64_t    offset;
      };

      struct TextureData
      {
        uint32_t     textureUnit;
        TextureType  textureType;
        Ref<Texture> texture;
        Ref<Sampler> sampler;
      };

      ctHashMap<ctString, ValueData>   m_values;
      ctHashMap<ctString, TextureData> m_textures;

      int64_t m_blockIndex = -1;

      ctVector<uint8_t> m_shaderData;
      ctVector<uint8_t> m_activeShaderData;
      Ref<UniformBuffer> m_uniformBuffer;
    };
}
