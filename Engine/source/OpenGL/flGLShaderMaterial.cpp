#include "flUniformBuffer.h"
#include "flProgram.h"
#include "flTexture.h"
#include "flSampler.h"
#include "flAPI.h"
#include "flGLShaderMaterial.h"
#include "flGLUtil.h"

namespace Fractal
{
  GLShaderMaterial::GLShaderMaterial(API* pAPI, Program* pProgram, char const* blockName)
    : ShaderMaterial(pAPI)
  {
    int64_t blockIndex = pProgram->FindUniformBlock(blockName);
    int64_t blockSize  = pProgram->GetUniformBlockSize(blockIndex);

    m_shaderData.resize(blockSize);

    for (int64_t i = 0; i < pProgram->GetUniformCount(); ++i)
    {
      if (blockIndex != -1 && pProgram->GetUniformBlockIndex(i) == blockIndex)
      {
        // Get uniforms from the uniform block
        ValueData valueData;
        valueData.offset = pProgram->GetUniformBlockOffset(i);
        pProgram->GetUniformDataType(i, &valueData.type, &valueData.width);
        m_values.Add(pProgram->GetUniformName(i), valueData);
      }
      else
      {
        // Get texture slots
        TextureData textureData;
        if (pProgram->GetUniformSamplerType(i, &textureData.textureType))
        {
          char const* name = pProgram->GetUniformName(i);
          textureData.textureUnit = pProgram->GetInt(name);
          m_textures.Add(name, textureData);
        }
      }
    }

    if (blockIndex >= 0)
      m_uniformBuffer = MakeRef(GetAPI()->CreateUniformBuffer(m_shaderData.size(), m_shaderData.data()), false);

    m_blockIndex = blockIndex;
  }

  ShaderMaterial* GLShaderMaterial::Create(API* pAPI, Program* pProgram, char const* blockName)
  {
    return flNew GLShaderMaterial(pAPI, pProgram, blockName);
  }

  void GLShaderMaterial::Apply()
  {
    if (m_uniformBuffer != nullptr && m_shaderData != m_activeShaderData)
      m_uniformBuffer->GetBuffer()->Set(m_shaderData.data(), m_shaderData.size());
  }

  void GLShaderMaterial::Bind(int64_t blockIndex)
  {
    if (m_uniformBuffer != nullptr)
      m_uniformBuffer->Bind(blockIndex);

    for (auto& kvp : m_textures)
    {
      flVerifyGL(glActiveTexture, GL_TEXTURE0 + kvp.m_val.textureUnit);

      if (kvp.m_val.texture != nullptr)
        kvp.m_val.texture->Bind();
      else
        flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);

      if (kvp.m_val.sampler != nullptr)
        kvp.m_val.sampler->Bind(kvp.m_val.textureUnit);
      else
        flVerifyGL(glBindSampler, 0, 0);
    }
  }

  bool GLShaderMaterial::SetValue(char const* name, float value)
  {
    return SetValue(name, &value, Type_Float32, 1);
  }

  bool GLShaderMaterial::SetValue(char const* name, float const* pValues, int64_t componentCount)
  {
    return SetValue(name, pValues, TypeOf<float>(), componentCount);
  }

  bool GLShaderMaterial::SetValue(char const* name, void const* pValue, Type const& type, int64_t const& width)
  {
    ValueData* pValueData = m_values.TryGet(name);
    if (pValueData == nullptr)
      return false;

    void* pDst = m_shaderData.data() + pValueData->offset;
    ConvertPrimitive(pDst, pValueData->type, pValue, type, ctMin(width, pValueData->width));
    return true;
  }

  bool GLShaderMaterial::SetTexture(char const* name, Texture* pTexture)
  {
    TextureData* pTextureData = m_textures.TryGet(name);
    if (pTextureData == nullptr)
      return false;

    pTextureData->texture = MakeRef(pTexture, true);
    return true;
  }

  bool GLShaderMaterial::SetSampler(char const* name, Sampler* pSampler)
  {
    TextureData* pTextureData = m_textures.TryGet(name);
    if (pTextureData == nullptr)
      return false;

    pTextureData->sampler = MakeRef(pSampler, true);
    return true;
  }
}