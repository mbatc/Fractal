#include "flGLHardwareBuffer.h"
#include "flGLUtil.h"

namespace Fractal
{
  GLHardwareBuffer* GLHardwareBuffer::Create(API* pAPI, BufferBinding binding, BufferUsage usage)
  {
    return flNew GLHardwareBuffer(pAPI, binding, usage);
  }

  GLHardwareBuffer::GLHardwareBuffer(API* pAPI, BufferBinding binding, BufferUsage usage)
    : HardwareBuffer(pAPI)
  {
    flVerifyGL(glCreateBuffers, 1, &m_bufferID);
    m_binding      = binding;
    m_usageFlag    = usage;
    m_glUsageFlags = GLUtil::ToBufferUsage(usage);
  }

  GLHardwareBuffer::~GLHardwareBuffer()
  {
    flVerifyGL(glDeleteBuffers, 1, &m_bufferID);
  }

  bool GLHardwareBuffer::Resize(int64_t size, bool discardData)
  {
    bool success = true;
    if (size > m_gpuSize)
    {
      // Reallocate
      uint8_t* pNewData = nullptr;
      if (!discardData)
      {
        void* pMapped = Map(AccessFlag_Read);
        if (!pMapped)
          return false;

        pNewData = flNew uint8_t[size];
        memcpy(pNewData, pMapped, min(size, m_size));
        Unmap();
      }

      bool success = Set(pNewData, size);
      flDelete[] pNewData;
      m_gpuSize = size;
    }

    m_size = size;
    return success;
  }

  bool GLHardwareBuffer::Set(void const* pData, int64_t size)
  {
    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, m_bufferID);
    flVerifyGL(glBufferData, GL_COPY_WRITE_BUFFER, (GLsizeiptr)size, pData, m_glUsageFlags);
    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, 0);
    m_size = size;
    return true;
  }

  bool GLHardwareBuffer::Get(void* pBuffer, int64_t length, int64_t offset)
  {
    void* pMapped = Map(AccessFlag_Read, length, offset);
    if (!pMapped)
      return false; // Buffer is already mapped in an incompatible way.

    memcpy(pBuffer, pMapped, length);
    Unmap();
    return true;
  }

  int64_t GLHardwareBuffer::GetSize() const
  {
    return m_size;
  }

  BufferUsage GLHardwareBuffer::GetBufferUsage() const
  {
    return m_usageFlag;
  }

  BufferBinding GLHardwareBuffer::GetBinding() const
  {
    return m_binding;
  }

  void* GLHardwareBuffer::Map(AccessFlags flags, int64_t length, int64_t offset)
  {
    int64_t mappedLength = length;
    if (length < 0)
      mappedLength = m_size;

    if (m_pMappedPtr)
    {
      // The buffer is already mapped - check if we can still return a valid pointer
      if ((m_mappedFlags & flags) == 0)
        return nullptr;
      if (offset < m_mappedOffset)
        return nullptr; // Starts before m_pMappedPtr
      if (offset + mappedLength > m_mappedOffset + m_mappedLength)
        return nullptr; // Ends after m_pMappedPtr + m_mappedLength
      ++m_mappedCount;
      return (uint8_t*)m_pMappedPtr + offset;
    }

    GLenum glAccess = 0;
    if (flags == AccessFlag_Read)
      glAccess = GL_READ_ONLY;
    if (flags == AccessFlag_Write)
      glAccess = GL_WRITE_ONLY;
    if (flags == AccessFlag_ReadWrite)
      glAccess = GL_READ_WRITE;
    if (glAccess == 0)
      return nullptr;

    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, m_bufferID);
    m_pMappedPtr = flVerifyGL(glMapBuffer, GL_COPY_WRITE_BUFFER, glAccess);
    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, 0);

    if (!m_pMappedPtr)
      return nullptr;

    m_mappedCount = 1;
    m_mappedOffset = offset;
    m_mappedLength = mappedLength;

    return m_pMappedPtr;
  }

  bool GLHardwareBuffer::Unmap()
  {
    if (m_mappedCount == 0)
      return false;

    if (--m_mappedCount > 0)
      return true;

    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, m_bufferID);
    flAssert(flVerifyGL(glUnmapBuffer, GL_COPY_WRITE_BUFFER), "Unmap buffer failed");
    flVerifyGL(glBindBuffer, GL_COPY_WRITE_BUFFER, 0);

    m_pMappedPtr = nullptr;
    return true;
  }

  void* GLHardwareBuffer::GetNativeResource() const
  {
    return flNativeFromGLID(m_bufferID);
  }
}
