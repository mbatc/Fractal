#ifndef flProgramDetails_h__
#define flProgramDetails_h__

namespace flEngine
{
  namespace Graphics
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
      ProgramStage_Count
    };
  }
}

#endif // flProgramDetails_h__
