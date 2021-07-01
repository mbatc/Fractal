#pragma once

namespace Fractal
{
    enum ProgramStage
    {
      ProgramStage_Unknown = -1,
      ProgramStage_Vertex,
      ProgramStage_Fragment,
      ProgramStage_Geometry,
      ProgramStage_TessControl,
      ProgramStage_TessEval,
      ProgramStage_Compute,
      ProgramStage_Count,
    };

    enum DrawMode
    {
      DrawMode_Lines,
      DrawMode_LineLoop,
      DrawMode_Points,
      DrawMode_Triangles,
      DrawMode_TriangleFan,
      DrawMode_TriangleStrip,
      DrawMode_Patches,
      DrawMode_Count,
    };
}
