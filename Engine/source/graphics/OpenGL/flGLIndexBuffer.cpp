#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLIndexBuffer
    {
    public:
      ~Impl_GLIndexBuffer() { glDeleteBuffers(1, &m_bufferID); }

      void Construct(flIN AccessFlags accessFlags)
      {
        glCreateBuffers(1, &m_bufferID);
        m_accessFlags = accessFlags;
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, pData, m_glAccessFlags);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

      bool Update()
      {
        return true;
      }

      int64_t GetSize()
      {
        return m_size;
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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        m_pMappedPtr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, offset, mappedLength, glAccess);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
      AccessFlags m_accessFlags = AF_None;

      // Description of the mapped client memory
      void       *m_pMappedPtr = nullptr;
      int64_t     m_mappedOffset = 0;
      int64_t     m_mappedLength = 0;
      AccessFlags m_mappedFlags = AF_None;

      // The number of calls to Map() where a valid pointer was returned.
      // Unmap should be called this many times.
      int64_t     m_mappedCount = 0;
    };
  }
}


using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLIndexBuffer);
#define flIMPL flPIMPL(GLIndexBuffer)

GLIndexBuffer::GLIndexBuffer(flIN AccessFlags accessFlags)
{
  flIMPL->Construct(accessFlags);
}

GLIndexBuffer* GLIndexBuffer::Create(flIN AccessFlags accessFlags)
{
  return flNew GLIndexBuffer(accessFlags);
}

bool GLIndexBuffer::Resize(flIN int64_t size, flIN bool discardData)
{
  return flIMPL->Resize(size, discardData);
}

bool GLIndexBuffer::Set(flIN void *pData, flIN int64_t size)
{
  return flIMPL->Set(pData, size);
}

bool GLIndexBuffer::Get(flOUT void *pBuffer, flIN int64_t length, flIN int64_t offset)
{
  return flIMPL->Get(pBuffer, length, offset);
}

bool GLIndexBuffer::Update()
{
  return flIMPL->Update();
}

int64_t GLIndexBuffer::GetSize()
{
  return flIMPL->GetSize();
}

AccessFlags GLIndexBuffer::GetAccessFlags()
{
  return flIMPL->GetAccessFlags();
}

void* GLIndexBuffer::Map(flIN AccessFlags flags, flIN int64_t length, flIN int64_t offset)
{
  return flIMPL->Map(flags, length, offset);
}

bool GLIndexBuffer::Unmap()
{
  return flIMPL->Unmap();
}

void* GLIndexBuffer::GetNativeResource()
{
  return flIMPL->GetNativeResource();
}
