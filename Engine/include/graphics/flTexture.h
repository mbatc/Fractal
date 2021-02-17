#ifndef fl_Graphics_Texture_h__
#define fl_Graphics_Texture_h__

#include "../flInterface.h"
#include "../math/flMath.h"
#include "flPixelFormat.h"

namespace flEngine
{
  namespace Graphics
  {
    /**
     * @brief An enumeration containing supported pixel types.
     */
    enum class PixelBufferType
    {
      Unknown = -1, ///< An unknown pixel buffer type.
      Colour,       ///< Indicates a pixel buffer containing Colour data.
      Depth,        ///< Indicates a pixel buffer containing Depth data.
      Count,        ///< The number of pixel buffer types.
    };

    /**
     * @brief A structure used to describe the format of pixel data.
     */
    struct flEXPORT PixelBufferDesc
    {
      PixelBufferType type; ///< The type of the pixel data.

      int64_t width;  ///< The width of the pixel data.
      int64_t height; ///< The height of the pixel data.
      int64_t depth;  ///< The depth of the pixel data (e.g. for a 3D texture).

      union
      {
        struct ColourDesc
        {
          PixelFormat format;      ///< The format of the pixel components.
          PixelComponentType type; ///< The type of each component in the pixels.
        } colour; ///< Data describing a colour pixel buffer. (used if type == PBT_Colour).

        struct DepthDesc
        {
          DepthFormat format; ///< The format of the depth data.
        } depth; ///< Data describing a depth pixel buffer. (used if type == PBT_Depth).
      };
    };

    class flEXPORT Texture : public Interface
    {
    public:
      /**
       * @brief Set the pixel data for this texture.
       *
       * @param [in] pPixels A pointer to a buffer containing the pixel data.
       * @param [in] format  The format of the pixel data.
       * @param [in] type    The type of the pixel data components.
       * @param [in] mipMap  The mip-map layer to copy the pixel data to.
       *
       * @return Returns true if the pixel data was set without errors, otherwise returns false.
       */
      virtual bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) = 0;

      /**
       * @brief Set the pixel data for this texture.
       *
       * @param [in] pPixels A pointer to a buffer containing the pixel data.
       * @param [in] size    The dimensions of the pixel data buffer.
       * @param [in] format  The format of the pixel data.
       * @param [in] type    The type of the pixel data components.
       * @param [in] offset  The starting coordinate when copying the pixel data into the texture.
       * @param [in] mipMap  The mip-map layer to copy the pixel data to.
       *
       * @return Returns true if the pixel data was set without errors, otherwise returns false.
       */
      virtual bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN Math::Vec3I offset = Math::Vec3I::zero(), flIN int64_t mipMap = 0) = 0;

      /**
       * @brief Download the textures pixel data into client memory.
       *
       * This function will download the texture pixel data and copy into a buffer. The pixel data
       * will be transformed into the format specified by the 'pBufferDesc' parameter. The to the
       * buffer allocated will be copied into ppPixels. This buffer must be freed using
       * flEngine::Memory::Free.
       *
       * The dimensions of the allocated buffer will be:
       * 
       *   GetWidth(mipMap) x GetHeight(mipMap) x GetDepth(mipMap)
       *
       * @param [out]     ppPixels    A pointer to pointer variable to copy the address of the allocated buffer to.
       * @param [in, out] pBufferDesc The format to retrieve the pixel data as. If the format type is left as unknown,
       *                              the pixel data will be retrieved in its internal format. The dimensions of the
       *                              pixel buffer returned will also be copied into this struct. Must not be NULL.
       * @param [in]      mipMap      The mip-map layer to retrieve.
       *
       * @return Returns true if the texture data was copied into ppPixels.
       */
      virtual bool Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) = 0;

      /**
       * @brief Generate mip-map layers for this texture.
       *
       * @return Returns true if mip-maps were generated, otherwise returns false.
       */
      virtual bool GenerateMipMaps() = 0;

      /**
       * @brief Check if this texture has mip-maps.
       *
       * @return Returns true if this texture has mip-maps.
       */
      virtual bool HasMipmaps() const = 0;
      
      /**
       * @brief Get the number of mip-map layers this texture has.
       *
       * @return The number of mip-map layers.
       */
      virtual int64_t GetMimMapCount() const = 0;

      /**
       * @brief Get the width of the texture.
       *
       * @return The width of the texture in pixels.
       */
      virtual int64_t GetWidth(flIN int64_t mipMap = 0) const = 0;

      /**
       * @brief Get the height of the texture.
       *
       * @return The height of the texture in pixels.
       */
      virtual int64_t GetHeight(flIN int64_t mipMap = 0) const = 0;

      /**
       * @brief Get the depth of the texture (e.g. a 3D texture).
       *
       * @return The depth of the texture in pixels.
       */
      virtual int64_t GetDepth(flIN int64_t mipMap = 0) const = 0;

      /**
       * @brief Get the PixelBufferType this texture was created with.
       *
       * @return The PixelBufferType of this texture.
       */
      virtual PixelBufferType GetPixelBufferType() const = 0;

      /**
      * @brief Get the PixelBufferDesc this texture was created with.
      *
      * @return The PixelBufferDesc for this texture.
      */
      virtual PixelBufferDesc* GetPixelBufferDesc() const = 0;
    };
  }
}

#endif // fl_Graphics_Texture_h__
