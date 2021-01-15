#ifndef fl_Graphics_GLIndexBuffer_h__
#define fl_Graphics_GLIndexBuffer_h__

#include "../flIndexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLIndexBuffer);

    class flEXPORT GLIndexBuffer : public IndexBuffer
    {
      flPIMPL_DEF(GLIndexBuffer);

      GLIndexBuffer(flIN AccessFlags accessFlags);

    public:
      static GLIndexBuffer* Create(flIN AccessFlags accessFlags);

      /**
      * @brief Resize the buffer.
      */
      virtual bool Resize(flIN int64_t size, flIN bool discardData = false) override;

      /**
      * @brief Set the buffer the data.
      */
      virtual bool Set(flIN void *pData, flIN int64_t size) override;

      /**
      * @brief Read data from the buffer.
      */
      virtual bool Get(flOUT void *pBuffer, flIN int64_t length = -1, flIN int64_t offset = 0) override;

      /**
      * @brief Apply any changes made to the buffer.
      */
      virtual bool Update() override;

      /**
      * @brief Get the size of the buffer.
      */
      virtual int64_t GetSize() override;

      /**
      * @brief GEt the access flags for this buffer.
      */
      virtual AccessFlags GetAccessFlags() override;

      /**
      * @brief Map the buffer to client memory.
      *
      * @return A pointer to the buffer.
      */
      virtual void* Map(flIN AccessFlags flags, flIN int64_t length = -1, flIN int64_t offset = 0) override;

      /**
      * @brief Unmap the buffer from client memory.
      */
      virtual bool Unmap() override;

      /**
      *
      */
      virtual void* GetNativeResource() override;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
