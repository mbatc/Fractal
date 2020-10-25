#ifndef flGraphics_h__
#define flGraphics_h__

#include "../utility/flConfig.h"
#include "../utility/flMath.h"

namespace flEngine
{
  namespace Graphics
  {
    class API;

    class flEXPORT Canvas
    {
    public:
      virtual void AddText(const Math::Vec2F &pos, const char *str, uint32_t color = 0xFFFFFFFF, const float &scale = 1.0f, const char *pEnd = nullptr) = 0;
      virtual void AddLine(const Math::Vec2F &a, const Math::Vec2F &b, uint32_t color, float thinkness = 1.0f) = 0;
      virtual void AddRect(const Math::Vec2F &a, const Math::Vec2F &b, uint32_t color, float rounding = 0.0f, float thickness = 1.0f) = 0;
      virtual void AddRectFilled(const Math::Vec2F &a, const Math::Vec2F &b, uint32_t color, float rounding = 0.0f) = 0;
      virtual void AddRectColoured(const Math::Vec2F &a, const Math::Vec2F &b, uint32_t tlColor, uint32_t trColor, uint32_t blColor, uint32_t brColor, float rounding = 0.0f, float thickness = 1.0f) = 0;
      virtual void AddRectColouredFilled(const Math::Vec2F &a, const Math::Vec2F &b, uint32_t tlColor, uint32_t trColor, uint32_t blColor, uint32_t brColor, float rounding = 0.0f) = 0;
      virtual void AddRectTextured(atTexture *pTexture, const Math::Vec2F &a, const Math::Vec2F &b, uint32_t color = 0xFFFFFFFF, const Math::Vec2F &tlUV = { 0, 0 }, const Math::Vec2F &brUV = { 1, 1 }, float rounding = 0.0f) = 0;

      virtual void AddPolyline(Math::Vec2F *pPoints, uint32_t *pColors, int64_t nPoints, bool closed, float thickness = 1.0f) = 0;
      virtual void AddPolylineTextured(atTexture *pTexture, Math::Vec2F *pPoints, uint32_t *pColors, int64_t nPoints, const Math::Vec2F &minTexCoord = { 0, 0 }, const Math::Vec2F &maxTexCoord = { 1, 1 }) = 0;
      virtual void AddPolylineConcaveFilled(Math::Vec2F *pPoints, uint32_t *pColors, int64_t nPoints) = 0;

      virtual void AddPath(bool closed, float thickness = 1.0f) = 0;
      virtual void AddPathConcaveFilled() = 0;
      virtual void PathClear() = 0;
      virtual void PathColor(const uint32_t &color) = 0; // Set the colour assigned to new points added
      virtual void PathRect(const Math::Vec2F &a, const Math::Vec2F &b, float rounding = 0.0f, uint32_t tlCol = 0xFFFFFFFF, uint32_t trCol = 0xFFFFFFFF, uint32_t blCol = 0xFFFFFFFF, uint32_t brCol = 0xFFFFFFFF) = 0;
      virtual void PathLineTo(const Math::Vec2F &a) = 0;
      virtual void PathArc(const Math::Vec2F &center, float radius, float angleStart, float angle, int64_t nSegments = 10) = 0;

      virtual void Clear() = 0;
      virtual int64_t VertexCount() const = 0;
      virtual int64_t IndexCount() const = 0;
      virtual int64_t CmdCount() const = 0;

      virtual bool Render(API *pAPI) = 0;
    };
  };
};

#endif // flGraphics_h__
