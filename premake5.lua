function fmtPath(path)
  while true do
    path, num = path:gsub("\\\\", "\\")
    if num == 0 then
      break
    end
  end
  return path
end

function getCopyCommand (src, dst)
  src = fmtPath(src)
  dst = fmtPath(dst)
  return "copy \"" .. src .. "\" \"" .. dst .. "\" /y"
end

workspace "Fractal"
  configurations {"Debug", "Release" }
  startproject "FractalEditor"

  -- Setup global properties for the Debug configuration
  filter { "configurations:Debug" }
    runtime         "Debug"
    optimize        "Off"
    symbols         "On"
    inlining        "Default"
    floatingpoint   "Fast"
    editandcontinue "On"
    defines         { "DEBUG"}

  -- Setup global properties for the Release configuration
  filter { "configurations:Release" }
    runtime         "Release"
    optimize        "On"
    symbols         "On"
    inlining        "Auto"
    floatingpoint   "Fast"
    editandcontinue "Off"
    flags           { "LinkTimeOptimization" }
    defines         { "NDEBUG" }

  -- Project Flags
  flags { "FatalWarnings" }
  flags { "MultiProcessorCompile" }

  -- Linker options
  linkoptions { "/ignore:4006" }
  linkoptions { "/ignore:4221" }
  linkoptions { "/ignore:4075" }

  win32Build = os.target() == "windows"
  linuxBuild = os.target() == "linux"

  if (not win32Build and not linuxBuild) then
    print("This operating system is not supported.")
    exit()
  end
  
  -- Setup std includes and libs for linux
  if (linuxBuild == true) then
    includedirs { "/usr/include" }
    libdirs {"/usr/lib"}
    print("Creating project for Linux...")
  end

  flBuildsPath = "../builds"
  flBinPath = flBuildsPath .. "/bin"
  ctools_bin = "../../../builds/bin"

  -- Allow linking to files in the bin folder
  libdirs { flBinPath }

  staticruntime "off"
  defines { "_CRT_SECURE_NO_WARNINGS" }

  -- Include ctools library modules
  group "ctools"
    dofile "ctools/setup/all-modules.lua"
  
  group "Fractal"
    -- Generate Fractal Engine Projects
    dofile "Engine/project.lua"
      location "Engine/"
  
    dofile "Editor/project.lua"
      location "Editor/"

    dofile "Player/project.lua"
      location "Player/"

  -- The test bed project
  group "Test Site"
    dofile "TechArea49/project.lua"
      location "TechArea49/"
