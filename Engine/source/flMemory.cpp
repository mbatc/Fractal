#include "flMemory.h"
#include <malloc.h>

namespace Fractal
{
  flEXPORT void* Alloc(flIN int64_t size)
  {
    return malloc(size);
  }

  flEXPORT void Free(flIN void* pBuffer)
  {
    return free(pBuffer);
  }

  flEXPORT void* Realloc(flIN flOUT void* pBuffer, flIN int64_t size)
  {
    return realloc(pBuffer, size);
  }
}
