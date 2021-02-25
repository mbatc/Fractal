#include "graphics/flTexture.h"

using namespace flEngine::Graphics;

flEXPORT void CreatePixelBufferDesc(flOUT PixelBufferDesc *pDesc, flIN PixelFormat format, flIN PixelComponentType type, flIN int64_t width, flIN int64_t height, flIN int64_t depth)
{
  pDesc->type = PixelBufferType_Colour;
  pDesc->colourDesc.format = format;
  pDesc->colourDesc.type = type;
  pDesc->width = width;
  pDesc->height = height;
  pDesc->depth = depth;
}

flEXPORT void CreatePixelBufferDesc(flOUT PixelBufferDesc *pDesc, flIN DepthFormat format, flIN int64_t width, flIN int64_t height, flIN int64_t depth)
{
  pDesc->type = PixelBufferType_Depth;
  pDesc->depthDesc.format = format;
  pDesc->width = width;
  pDesc->height = height;
  pDesc->depth = depth;
}

flEXPORT int64_t GetPixelStride(flIN PixelBufferDesc *pDesc)
{
  if (pDesc->type == PixelBufferType_Depth)
    return GetDepthFormatSize(pDesc->depthDesc.format);
  else if (pDesc->type == PixelBufferType_Colour)
    return GetPixelComponentCount(pDesc->colourDesc.format) * GetPixelComponentSize(pDesc->colourDesc.type);
  return 0;
}