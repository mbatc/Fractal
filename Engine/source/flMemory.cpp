#include "flMemory.h"
#include <malloc.h>

using namespace flEngine::Memory;

flEXPORT void* flEngine::Memory::Alloc(flIN int64_t size)
{
  return malloc(size);
}

flEXPORT void flEngine::Memory::Free(flIN void *pBuffer)
{
  return free(pBuffer);
}

flEXPORT void* flEngine::Memory::Realloc(flIN flOUT void *pBuffer, flIN int64_t size)
{
  return realloc(pBuffer, size);
}
