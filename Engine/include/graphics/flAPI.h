#ifndef fl_Graphics_API_h__
#define fl_Graphics_API_h__

#include "../threads/flThreadQueue.h"

namespace flEngine
{
  namespace Graphics
  {
    class Geometry;
    class Program;
    class RenderTarget;
    class IndexBuffer;
    class VertexBuffer;
    class PixelBuffer;
    class DeviceState;
    class WindowRenderTarget;
    class TextureRenderTarget;

    struct flEXPORT APIConfig
    {
      int64_t multisampleCount;
    };

    class flEXPORT API : public Interface
    {
    public:
      /**
       * @brief Set the active geometry to be rendered.
       */
      virtual void SetGeometry(Geometry *pGeometry) = 0;

      /**
       * @brief Set the destination for the render.
       */
      virtual void SetRenderTarget(RenderTarget *pRenderTarget) = 0;

      /**
       * @brief Set the GPU program to render.
       */
      virtual void SetProgram(Program *pProgram) = 0;

      /**
      * @brief Get a pointer the the GPU's state interface.
      */
      virtual DeviceState* GetState() = 0;

      /**
       * @brief Execute a render command.
       */
      virtual void Render() = 0;

      virtual WindowRenderTarget* CreateWindowRenderTarget() = 0;

      virtual TextureRenderTarget* CreateTextureRenderTarget() = 0;
      
      virtual Geometry* CreateGeometry() = 0;
      
      virtual IndexBuffer* CreateIndexBuffer() = 0;
      
      virtual VertexBuffer* CreateVertexBuffer() = 0;
      
      virtual PixelBuffer* CreatePixelBuffer() = 0;
      
      virtual Program* CreateProgram() = 0;
    };

    Threads::ThreadQueue renderThread;
  }
}

#endif // fl_Graphics_API_h__
