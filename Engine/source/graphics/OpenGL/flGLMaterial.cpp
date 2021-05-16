#include "graphics/flUniformBuffer.h"
#include "graphics/flProgram.h"
#include "graphics/flTexture.h"
#include "graphics/flSampler.h"
#include "graphics/flAPI.h"
#include "flGLMaterial.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    GLMaterial::GLMaterial(API *pAPI, Program *pProgram, char const *blockName)
      : Material(pAPI)
    {
      int64_t blockIndex = pProgram->FindUniformBlock(blockName);
      int64_t blockSize  = pProgram->GetUniformBlockSize(blockIndex);

      m_shaderData.resize(blockSize);

      for (int64_t i = 0; i < pProgram->GetUniformCount(); ++i)
      {
        if (blockIndex != -1 && pProgram->GetUniformBlockIndex(i) == blockIndex)
        { // Get uniforms from the uniform block
          ValueData valueData;
          valueData.offset = pProgram->GetUniformBlockOffset(i);
          pProgram->GetUniformDataType(i, &valueData.type, &valueData.width);
          m_values.Add(pProgram->GetUniformName(i), valueData);
        }
        else
        { // Get texture slots
          TextureData textureData;
          if (pProgram->GetUniformSamplerType(i, &textureData.textureType))
          {
            char const *name = pProgram->GetUniformName(i);
            textureData.textureUnit = pProgram->GetInt(name);
            m_textures.Add(name, textureData);
          }
        }
      }

      if (blockIndex >= 0)
        m_uniformBuffer = MakeRef(GetAPI()->CreateUniformBuffer(m_shaderData.size(), m_shaderData.data()), false);

      m_blockIndex = blockIndex;
    }

    Material* GLMaterial::Create(API *pAPI, Program *pProgram, char const * blockName)
    {
      return flNew GLMaterial(pAPI, pProgram, blockName);
    }

    void GLMaterial::Apply()
    {
      if (m_shaderData != m_activeShaderData)
        m_uniformBuffer->GetBuffer()->Set(m_shaderData.data(), m_shaderData.size());
    }

    void GLMaterial::Bind()
    {
      m_uniformBuffer->Bind(m_blockIndex);

      for (auto &kvp : m_textures)
      {
        glActiveTexture(GL_TEXTURE0 + kvp.m_val.textureUnit);

        if (kvp.m_val.texture != nullptr) kvp.m_val.texture->Bind();
        else                              glBindTexture(GL_TEXTURE_2D, 0);

        if (kvp.m_val.sampler != nullptr) kvp.m_val.sampler->Bind(kvp.m_val.textureUnit);
        else                              glBindSampler(0, 0);
      }
    }

    bool GLMaterial::SetValue(char const* name, float value)
    {
      return SetValue(name, &value, Util::Type_Float32, 1);
    }

    bool GLMaterial::SetValue(char const *name, float const *pValues, int64_t componentCount)
    {
      return SetValue(name, pValues, Util::TypeOf<float>(), componentCount);
    }

    bool GLMaterial::SetValue(char const * name, void const *pValue, Util::Type const &type, int64_t const &width)
    {
      ValueData *pValueData = m_values.TryGet(name);
      if (pValueData == nullptr)
        return false;

      void *pDst = m_shaderData.data() + pValueData->offset;
      Util::ConvertPrimitive(pDst, pValueData->type, pValue, type, ctMin(width, pValueData->width));
      return true;
    }

    bool GLMaterial::SetTexture(char const * name, Texture * pTexture)
    {
      TextureData *pTextureData = m_textures.TryGet(name);
      if (pTextureData == nullptr)
        return false;

      pTextureData->texture = MakeRef(pTexture, true);
      return true;
    }

    bool GLMaterial::SetSampler(char const * name, Sampler * pSampler)
    {
      TextureData *pTextureData = m_textures.TryGet(name);
      if (pTextureData == nullptr)
        return false;

      pTextureData->sampler = MakeRef(pSampler, true);
      return true;
    }
  }
}