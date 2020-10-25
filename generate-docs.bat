@echo off

mkdir documentation

cd Engine
"..\3rdParty\doxygen\doxygen.exe" Doxyfile

cd ..\Editor
"..\3rdParty\doxygen\doxygen.exe" Doxyfile

cd ..\Player
"..\3rdParty\doxygen\doxygen.exe" Doxyfile

cd ..