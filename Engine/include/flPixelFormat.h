#pragma once

#include "flConfig.h"

namespace Fractal
{
    /**
     * @brief An enumeration to describe different Pixel formats.
     */
    enum PixelFormat
    {
      PixelFormat_Unknown = -1, ///< The pixel format is unknown.
      PixelFormat_Red,          ///< Each pixel contains a Red component.
      PixelFormat_RG,           ///< Each pixel contains a Red and Green component.
      PixelFormat_RGB,          ///< Each pixel contains a Red, Green and Blue component.
      PixelFormat_RGBA,         ///< Each pixel contains a Red, Green, Blue and Alpha component.
      PixelFormat_Count,        ///< The number of supported pixel formats.
    };

    /**
     * @brief An enumeration describing different types for pixel components (Red, Green, Blue, Alpha).
     */
    enum PixelComponentType
    {
      PixelComponentType_Unknown = -1, ///< The type is unknown
      PixelComponentType_UInt8,        ///< Each component is an unsigned 8-bit integer.
      PixelComponentType_UInt16,       ///< Each component is a unsigned 16-bit integer.
      PixelComponentType_UInt32,       ///< Each component is a unsigned 32-bit integer.
      PixelComponentType_Int8,         ///< Each component is an 8-bit integer.
      PixelComponentType_Int16,        ///< Each component is a 16-bit integer.
      PixelComponentType_Int32,        ///< Each component is a 32-bit integer.
      PixelComponentType_Norm8,        ///< Each component is a signed 8-bit integer, when sampled, it is normalized between -1 and 1.
      PixelComponentType_Norm16,       ///< Each component is a signed 16-bit integer, when sampled, it is normalized between -1 and 1.
      PixelComponentType_UNorm8,       ///< Each component is an unsigned signed 8-bit integer, when sampled, it is normalized between 0 and 1.
      PixelComponentType_UNorm16,      ///< Each component is an unsigned signed 16-bit integer, when sampled, it is normalized between 0 and 1.
      PixelComponentType_Float16,      ///< Each component is a 16-bit float.
      PixelComponentType_Float32,      ///< Each component is a 32-bit float.
      PixelComponentType_Count,        ///< The number of supported pixel component types.
    };

    /**
    * @brief An enumeration describing different formats for depth pixels.
    */
    enum DepthFormat
    {
      DepthFormat_Unknown = -1,    ///< The depth format is unknown
      DepthFormat_Float16,         ///< 16-bit float depth buffer.
      DepthFormat_Float24,         ///< 24-bit float depth buffer.
      DepthFormat_Float32,         ///< 32-bit float depth buffer.
      DepthFormat_Float24Stencil8, ///< 24-bit float depth buffer, with an 8-bit stencil buffer.
      DepthFormat_Float32Stencil8, ///< 32-bit float depth buffer, with an 8-bit stencil buffer.
      DepthFormat_Count,           ///< The number of supported depth formats.
    };

    flEXPORT int64_t GetPixelComponentSize(flIN PixelComponentType type);
    flEXPORT int64_t GetPixelComponentCount(flIN PixelFormat type);
    flEXPORT int64_t GetDepthFormatSize(flIN DepthFormat type);
}
