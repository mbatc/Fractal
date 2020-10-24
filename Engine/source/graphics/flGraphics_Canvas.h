#ifndef flGraphics_h__
#define flGraphics_h__

#include "../utility/flConfig.h"

namespace flEngine
{
  namespace Graphics
  {
    class API;

    class flEXPORT Canvas
    {
    public:
      void AddText(const Math::Vec2F &pos, const char *str, atCol color = atColor::white, const float &scale = 1.0f, const char *pEnd = nullptr);
      void AddLine(const Math::Vec2F &a, const Math::Vec2F &b, atCol color, float thinkness = 1.0f);
      void AddRect(const Math::Vec2F &a, const Math::Vec2F &b, atCol color, float rounding = 0.0f, float thickness = 1.0f);
      void AddRectFilled(const Math::Vec2F &a, const Math::Vec2F &b, atCol color, float rounding = 0.0f);
      void AddRectColoured(const Math::Vec2F &a, const Math::Vec2F &b, atCol tlColor, atCol trColor, atCol blColor, atCol brColor, float rounding = 0.0f, float thickness = 1.0f);
      void AddRectColouredFilled(const Math::Vec2F &a, const Math::Vec2F &b, atCol tlColor, atCol trColor, atCol blColor, atCol brColor, float rounding = 0.0f);
      void AddRectTextured(atTexture *pTexture, const Math::Vec2F &a, const Math::Vec2F &b, atCol color = atColor::white, const Math::Vec2F &tlUV = { 0, 0 }, const Math::Vec2F &brUV = { 1, 1 }, float rounding = 0.0f);

      void AddPolyline(Math::Vec2F *pPoints, atCol *pColors, int64_t nPoints, bool closed, float thickness = 1.0f);
      void AddPolylineTextured(atTexture *pTexture, Math::Vec2F *pPoints, atCol *pColors, int64_t nPoints, const atVec2F &minTexCoord = { 0, 0 }, const atVec2F &maxTexCoord = { 1, 1 });
      void AddPolylineConcaveFilled(Math::Vec2F *pPoints, atCol *pColors, int64_t nPoints);

      void AddPath(bool closed, float thickness = 1.0f);
      void AddPathConcaveFilled();
      void PathClear();
      void PathColor(const atCol &color); // Set the colour assigned to new points added
      void PathRect(const Math::Vec2F &a, const atVec2F &b, float rounding = 0.0f, atCol tlCol = atColor::white, atCol trCol = atColor::white, atCol blCol = atColor::white, atCol brCol = atColor::white);
      void PathLineTo(const Math::Vec2F &a);
      void PathArc(const Math::Vec2F &center, float radius, float angleStart, float angle, int64_t nSegments = 10) = 0;

      void Clear() = 0;
      int64_t VertexCount() const = 0;
      int64_t IndexCount() const = 0;
      int64_t CmdCount() const = 0;
      virtual bool Render(API *pAPI) = 0;
    };
  };
};

#endif // flGraphics_h__
