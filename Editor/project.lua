
project "FractalEditor"
configurations { "Debug", "Release" }

if (not win32Build and not linuxBuild) then
  print("This operating system is not supported.")
  exit()
end

-- Setup WIN32 Project
if (win32Build == true) then
  defines { "atPLATFORM_WIN32" }
  print("Creating project for Windows...")
end

-- Setup Linux Project
if (linuxBuild == true) then
  defines { "atPLATFORM_LINUX" }
  includedirs { "/usr/include" }
  libdirs {"/usr/lib"}
  print("Creating project for Linux...")
end

dependson { "FractalEngine" }

kind "ConsoleApp"
architecture "x64"
language "C++"
characterset ("MBCS")

-- Set Directories

targetdir (flBinPath)
debugdir (flBinPath)
objdir (flBuildsPath .. "/output/%{cfg.platform}_%{cfg.buildcfg}")
symbolspath '$(OutDir)$(TargetName).pdb'

-- Project Flags

flags { "FatalWarnings" }
flags { "MultiProcessorCompile" }

-- Build Options

-- buildoptions { "/bigobj" }

-- Linker options

linkoptions { "/ignore:4006" }
linkoptions { "/ignore:4221" }
linkoptions { "/ignore:4075" }

-- Shared Defines

  defines { "_CRT_SECURE_NO_WARNINGS" }

-- Includes
  includedirs { "source/" } 
  includedirs { "source/**" } 

  -- atLib Includes
  includedirs { "../atLib/projects/atLib/include/" } 
  includedirs { "../atLib/projects/atLib/include/**" } 
  includedirs { "../atLib/projects/atLib/source/" } 
  includedirs { "../atLib/projects/atLib/source/**" }

  -- Third Party
  includedirs { "../atLib/projects/atLib/3rdParty" } 
  includedirs { "../atLib/projects/atLib/3rdParty/stb" }
  includedirs { "../atLib/projects/atLib/3rdParty/lua/include" }
  includedirs { "../atLib/projects/atLib/3rdParty/glew/include" }
  includedirs { "../atLib/projects/atLib/3rdParty/imgui" }
  includedirs { "../atLib/projects/atLib/3rdParty/fbxsdk/include" }

  includedirs { "../Engine/include/" } 

-- Project Files

  files { "source/**.cpp", "source/**.h", "source/**.inl" , "**.natvis" }

  links { "opengl32", "glew32", "atLib" }
  links { "FractalEngine" }
  
  libdirs { "../atLib/projects/atLib/3rdParty/glew/lib/Release/x64/" }
  libdirs { "../builds/bin/" }

-- Debug Configuration Settings

  filter { "configurations:Debug" }
    defines { "DEBUG"}
    symbols "On"
	  editandcontinue "On"

-- Release Configuration Settings

  filter { "configurations:Release" }
    flags { "LinkTimeOptimization" }
    defines { "NDEBUG" }
    optimize "On"
    editandcontinue "Off"
