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

    public:
      static GLIndexBuffer* Create();

      virtual bool Resize(int64_t size);

      /**
      * @brief Set the buffer the data.
      */
      virtual bool Set(void *pData, int64_t size);

      /**
      * @brief Read data from the buffer.
      */
      virtual bool Get(void *pBuffer, int64_t length, int64_t offset = 0);

      /**
      * @brief Apply any changes made to the buffer.
      */
      virtual bool Update();

      /**
      * @brief Get the size of the buffer.
      */
      virtual int64_t GetSize();

      /**
      * @brief GEt the access flags for this buffer.
      */
      virtual AccessFlags GetAccessFlags();

      /**
      * @brief Map the buffer to client memory.
      *
      * @return A pointer to the buffer.
      */
      virtual void* Map(flIN AccessFlags flags);

      /**
      * @brief Unmap the buffer from client memory.
      */
      virtual bool Unmap();
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
