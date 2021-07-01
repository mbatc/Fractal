#pragma once

#include "flConfig.h"

namespace Fractal
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
  flEXPORT void Free(flIN void* pBuffer);

  /**
   * @brief Attempt to reallocate a buffer.
   */
  flEXPORT void* Realloc(flIN flOUT void* pBuffer, flIN int64_t size);
}

#define flNew new
#define flDelete delete
#define flAlloc(size) Fractal::Alloc(size)
#define flRealloc(pMem, size) Fractal::Realloc(pMem, size)
#define flAllocT(type, count) (type*)flAlloc(sizeof(type) * count)
#define flFree(pMem) (Fractal::Free(pMem), pMem = nullptr)
