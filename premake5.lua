workspace "Fractal"
  configurations {"Debug", "Release" }
  startproject "atEngine"

  -- General Config
  atLibBuildPath = "..\\..\\..\\bin"

  staticruntime "off"

  dofile "atLib/projects/atLib/project.lua"
    location "atLib/projects/atLib/"
  
  dofile "Engine/project.lua"
    location "Engine/"
  
  dofile "Editor/project.lua"
    location "Editor/"

  dofile "Player/project.lua"
    location "Player/"
