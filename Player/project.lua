
project "FractalPlayer"
  configurations { "Debug", "Release" }
  
  dependson { "FractalEngine" }
  
  kind "ConsoleApp"
  architecture "x64"
  language "C++"
  cppdialect "C++17"
  characterset ("MBCS")

-- Set Directories
  targetdir (flBinPath)
  debugdir (flBinPath)
  objdir (flBuildsPath .. "/output/%{cfg.platform}_%{cfg.buildcfg}")
  symbolspath '$(OutDir)$(TargetName).pdb'

-- Includes
  includedirs { "include/" }
  includedirs { "../Engine/include/" } 

-- Project Files
  files { "source/**.cpp", "source/**.h", "source/**.inl" , "**.natvis" }

-- Third Party
  third_party_prefix = "../3rdParty/"
  dofile "../3rdParty/3rd-party.lua"

-- Lib links
  libdirs { flBuildsPath }
  links { "FractalEngine" }
