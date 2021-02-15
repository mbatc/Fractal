-- Get the 3rdParty root specified
if third_party_prefix == nil then
    third_party_prefix = "./"
end

-- Library Directories
glew_dir = third_party_prefix .. "glew/"
nanosvg_dir = third_party_prefix .. "nanosvg/"
ctools_module_dir = third_party_prefix .. "../ctools/modules/"

-- Library Includes
includedirs { third_party_prefix }
includedirs { nanosvg_dir .. "nanosvg/src" }
includedirs { glew_dir .. "include/" }
includedirs { ctools_module_dir .. "common/include" }
includedirs { ctools_module_dir .. "math/include" }
includedirs { ctools_module_dir .. "data/include" }
includedirs { ctools_module_dir .. "platform/include" }

libdirs { glew_dir .. "lib/Release/x64/" }

-- Library links
links { "ctools-common", "ctools-math", "ctools-data", "ctools-platform" } -- CTools
links { "glew32", "opengl32" }                                             -- Open GL

path_to_bin = third_party_prefix .. flBinPath

postbuildcommands {
    getCopyCommand(glew_dir .. "bin\\Release\\x64\\glew32.dll", path_to_bin .. "\\glew32.dll")
}
