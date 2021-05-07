#include "graphics/OpenGL/flGLHardwareBuffer.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLHardwareBuffer
    {
    public:
      ~Impl_GLHardwareBuffer() { glDeleteBuffers(1, &m_bufferID); }

      void Construct(flIN BufferBinding binding, flIN AccessFlags accessFlags)
      {
        glCreateBuffers(1, &m_bufferID);
        m_accessFlags = accessFlags;
        m_binding = binding;
        m_glAccessFlags = GL_STATIC_DRAW;
      }

      bool Resize(int64_t size, bool discardData)
      {
        void *pMapped = Map(AccessFlag_Read);
        if (!pMapped)
          return false;

        uint8_t *pNewData = nullptr;
        if (GetSize() > 0)
        {
          pNewData = flNew uint8_t[size];
          memcpy(pNewData, pMapped, min(size, m_size));
        }
        Unmap();
        bool success = Set(pNewData, size);
        flDelete[] pNewData;
        return success;
      }

      bool Set(void* pData, int64_t size)
      {
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_bufferID);
        glBufferData(GL_COPY_WRITE_BUFFER, (GLsizeiptr)size, pData, m_glAccessFlags);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        m_size = size;
        return true;
      }

      bool Get(void* pBuffer, int64_t length, int64_t offset)
      {
        void *pMapped = Map(AccessFlag_Read, length, offset);
        if (!pMapped)
          return false; // Buffer is already mapped in an incompatible way.

        memcpy(pBuffer, pMapped, length);
        Unmap();
        return true;
      }

      int64_t GetSize()
      {
        return m_size;
      }

      BufferBinding GetBinding()
      {
        return m_binding;
      }

      AccessFlags GetAccessFlags()
      {
        return m_accessFlags;
      }

      void* Map(AccessFlags flags, int64_t length = -1, int64_t offset = 0)
      {
        int64_t mappedLength = length;
        if (length < 0)
          mappedLength = m_size;

        if (m_pMappedPtr)
        { // The buffer is already mapped - check if we can still return a valid pointer
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
        if ((flags & AccessFlag_Read) > 0)  glAccess |= GL_MAP_READ_BIT;
        if ((flags & AccessFlag_Write) > 0) glAccess |= GL_MAP_WRITE_BIT;
        if (glAccess == 0)
          return nullptr;

        glBindBuffer(GL_COPY_WRITE_BUFFER, m_bufferID);
        m_pMappedPtr = glMapBufferRange(GL_COPY_WRITE_BUFFER, offset, mappedLength, glAccess);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

        if (!m_pMappedPtr)
          return nullptr;

        m_mappedCount = 1;
        m_mappedOffset = offset;
        m_mappedLength = mappedLength;

        return m_pMappedPtr;
      }

      bool IsMapped()
      {
        return m_pMappedPtr != nullptr;
      }

      bool Unmap()
      {
        if (m_mappedCount == 0)
          return false;

        if (--m_mappedCount > 0)
          return true;

        glBindBuffer(GL_COPY_WRITE_BUFFER, m_bufferID);
        glUnmapBuffer(GL_COPY_WRITE_BUFFER);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

        m_pMappedPtr = nullptr;
        return true;
      }

      void* GetNativeResource()
      {
        return (void*)(uint64_t)m_bufferID;
      }

    protected:
      int64_t m_size = 0;
      uint32_t m_bufferID = 0;

      GLenum m_glAccessFlags = 0;
      AccessFlags m_accessFlags = AccessFlag_None;
      BufferBinding m_binding = BufferBinding_Unknown;

      // Description of the mapped client memory
      void       *m_pMappedPtr = nullptr;
      int64_t     m_mappedOffset = 0;
      int64_t     m_mappedLength = 0;
      AccessFlags m_mappedFlags = AccessFlag_None;

      // The number of calls to Map() where a valid pointer was returned.
      // Unmap should be called this many times.
      int64_t     m_mappedCount = 0;
    };
  }
}


using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLHardwareBuffer);
#define flIMPL flPIMPL(GLHardwareBuffer)

GLHardwareBuffer* GLHardwareBuffer::Create(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  return flNew GLHardwareBuffer(binding, accessFlags);
}

GLHardwareBuffer::GLHardwareBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  flIMPL->Construct(binding, accessFlags);
}

bool GLHardwareBuffer::Resize(flIN int64_t size, flIN bool discardData)
{
  return flIMPL->Resize(size, discardData);
}

bool GLHardwareBuffer::Set(flIN void *pData, flIN int64_t size)
{
  return flIMPL->Set(pData, size);
}

bool GLHardwareBuffer::Get(flOUT void* pBuffer, flIN int64_t length, flIN int64_t offset)
{
  return flIMPL->Get(pBuffer, length, offset);
}

int64_t GLHardwareBuffer::GetSize() const
{
  return flIMPL->GetSize();
}

AccessFlags GLHardwareBuffer::GetAccessFlags() const
{
  return flIMPL->GetAccessFlags();
}

BufferBinding GLHardwareBuffer::GetBinding() const
{
  return flIMPL->GetBinding();
}

void* GLHardwareBuffer::Map(flIN AccessFlags flags, flIN int64_t length, flIN int64_t offset)
{
  return flIMPL->Map(flags, length, offset);
}

bool GLHardwareBuffer::Unmap()
{
  return flIMPL->Unmap();
}

void* GLHardwareBuffer::GetNativeResource() const
{
  return flIMPL->GetNativeResource();
}
