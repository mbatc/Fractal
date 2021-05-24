
project "FractalEngine"
  configurations { "Debug", "Release" }

  dependson { "ctools-common" }
  dependson { "ctools-data" }
  dependson { "ctools-math" }
  dependson { "ctools-platform" }
  dependson { "imgui" }

  kind "SharedLib"
  architecture "x64"
  language "C++"
  characterset ("MBCS")

  targetdir (flBinPath)
  debugdir (flBinPath)
  objdir (flBuildsPath .. "/output/%{cfg.platform}_%{cfg.buildcfg}")
  symbolspath '$(OutDir)$(TargetName).pdb'

-- Defines
  defines { "flCOMPILESHARED" }

-- Includes
  includedirs { "source/" } 
  includedirs { "include/" }

  -- Third Party
  third_party_prefix = "../3rdParty/"
  dofile "../3rdParty/3rd-party.lua"

-- Project Files
  files { "include/**.cpp", "include/**.h", "include/**.inl"}
  files { "source/**.cpp", "source/**.h", "source/**.inl" , "**.natvis" }

-- Lib Links
  libdirs { flBinPath }

