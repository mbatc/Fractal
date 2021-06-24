@echo off

REM Create directory to copy the artifact to
mkdir builds\artifact

cd

REM Copy binaries
copy /Y "builds\bin\FractalEditor.exe" "builds\artifact"
copy /Y "builds\bin\FractalPlayer.exe" "builds\artifact"
copy /Y "builds\bin\FractalEngine.dll" "builds\artifact"
copy /Y "builds\bin\glew32.dll" "builds\artifact"
