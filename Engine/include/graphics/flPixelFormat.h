#ifndef fl_Graphics_PixelFormat_h__
#define fl_Graphics_PixelFormat_h__

namespace flEngine
{
  namespace Graphics
  {
    /**
     * @brief An enumeration to describe different Pixel formats.
     */
    enum class PixelFormat
    {
      Unknown = -1, ///< The pixel format is unknown.
      Red,          ///< Each pixel contains a Red component.
      RG,           ///< Each pixel contains a Red and Green component.
      RGB,          ///< Each pixel contains a Red, Green and Blue component.
      RGBA,         ///< Each pixel contains a Red, Green, Blue and Alpha component.
      Count,        ///< The number of supported pixel formats.
    };

    /**
     * @brief An enumeration describing different types for pixel components (Red, Green, Blue, Alpha).
     */
    enum class PixelComponentType
    {
      Unknown = -1, ///< The type is unknown
      UInt8,        ///< Each component is an unsigned 8-bit integer.
      UInt16,       ///< Each component is a unsigned 16-bit integer.
      UInt32,       ///< Each component is a unsigned 32-bit integer.
      Int8,         ///< Each component is an 8-bit integer.
      Int16,        ///< Each component is a 16-bit integer.
      Int32,        ///< Each component is a 32-bit integer.
      UNorm8,       ///< Each component is a signed 8-bit integer, when sampled, it is normalized between -1 and 1.
      UNorm16,      ///< Each component is a signed 16-bit integer, when sampled, it is normalized between -1 and 1.
      Float16,      ///< Each component is a 16-bit float.
      Float32,      ///< Each component is a 32-bit float.
      Count,        ///< The number of supported pixel component types.
    };

    /**
    * @brief An enumeration describing different formats for depth pixels.
    */
    enum class DepthFormat
    {
      Unknown = -1,    ///< The depth format is unknown
      Float16,         ///< 16-bit float depth buffer.
      Float24,         ///< 24-bit float depth buffer.
      Float32,         ///< 32-bit float depth buffer.
      Float24Stencil8, ///< 24-bit float depth buffer, with an 8-bit stencil buffer.
      Float32Stencil8, ///< 32-bit float depth buffer, with an 8-bit stencil buffer.
      Count,           ///< The number of supported depth formats.
    };
  }
}

#endif // flPixelFormat_h__