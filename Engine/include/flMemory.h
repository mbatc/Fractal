#ifndef flMemory_h__
#define flMemory_h__

#include "flConfig.h"

namespace flEngine
{
  namespace Memory
  {
    /**
     * @brief Allocate a buffer of the specified size.
     * 
     * This functions wraps the standard c malloc() function.
     * This is done so that memory can be allocated/freed across module boundaries
     *
     * @param [in] size The size of the buffer to allocate in bytes.
     *
     * @return A pointer to the allocated buffer.
     */
    flEXPORT void* Alloc(flIN int64_t size);

    /**
     * @brief Release a buffer previously allocated with Alloc
     *
     * @param [in] pBuffer A pointer to the buffer to be freed.
     */
    flEXPORT void Free(flIN void *pBuffer);

    /**
     * @brief Attempt to reallocate a buffer.
     */
    flEXPORT void* Realloc(flIN flOUT void *pBuffer, flIN int64_t size);
  }
}

#define flNew new
#define flDelete delete
#define flAlloc(size) flEngine::Memory::Alloc(size)
#define flRealloc(pMem, size) flEngine::Memory::Realloc(pMem, size)
#define flAllocT(type, count) (type*)flAlloc(sizeof(type) * count)
#define flFree(pMem) (flEngine::Memory::Free(pMem), pMem = nullptr)

#endif // flMemory_h__
