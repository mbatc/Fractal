#pragma once

namespace Fractal
{
    enum BufferUsage
    {
      BufferUsage_Default,
      BufferUsage_Dynamic,
      BufferUsage_Immutable,
      BufferUsage_Staging,
      BufferUsage_Count
    };

    enum AccessFlags
    {
      AccessFlag_None = 0,
      AccessFlag_Read = 1 << 0,
      AccessFlag_Write = 1 << 1,
      AccessFlag_ReadWrite = (int64_t)AccessFlag_Read | AccessFlag_Write,
    };

    enum BufferBinding
    {
      BufferBinding_Unknown = -1,
      BufferBinding_Indices,
      BufferBinding_Vertices,
      BufferBinding_Uniforms,
      BufferBinding_Count,
    };
}
