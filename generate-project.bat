@echo off
cd "%~dp0"
echo What type of Project file should we generate? Select an option from the list below.
echo   [1] Visual Studio 2015
echo   [2] Visual Studio 2019

set /p opt="Selection: "

:PARSE_OPT

echo %opt%

IF %opt%==1 (
  call "setup\win\GenerateProject-vs2015.bat"
  goto VALID_OPT
)

IF %opt%==2 (
  call "setup\win\GenerateProject-vs2019.bat"
  goto VALID_OPT
)

IF "%opt%"=="q" (
  exit 1
)

set /p opt="Selected option is invalid. Choose again (or 'q' to exit): "
goto PARSE_OPT

:VALID_OPT

pause