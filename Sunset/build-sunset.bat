@echo off
setlocal

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Debug

set PLATFORM=PS3
set ROOT=%~dp0
if "%ROOT:~-1%"=="\" set ROOT=%ROOT:~0,-1%
set PROJ=%ROOT%\ps3-mc-modloader.vcxproj

if "%SCE_PS3_ROOT%"=="" set SCE_PS3_ROOT=C:\usr\local\cell
if "%SN_PS3_PATH%"=="" set SN_PS3_PATH=C:\usr\local\cell\host-win32\sn

set SCETOOL_EXE=%SCETOOL_EXE%
if "%SCETOOL_EXE%"=="" set SCETOOL_EXE=C:\Users\liams\Downloads\scetool\scetool.exe
set SCETOOL_WORK_DIR=%SCETOOL_WORK_DIR%
if "%SCETOOL_WORK_DIR%"=="" set SCETOOL_WORK_DIR=%ROOT%\..\dependencies\scetool\bin

"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "%PROJ%" /t:Build /p:Configuration=%CONFIG% /p:Platform=%PLATFORM%
if errorlevel 1 exit /b 1

set PRX=%ROOT%\PS3_Debug\sunset.prx
if not exist "%PRX%" set PRX=%ROOT%\PS3_Debug\Sunset.prx
if not exist "%PRX%" (
  echo error: built PRX not found in %ROOT%\PS3_Debug
  exit /b 1
)

set SPRX=%PRX:.prx=.sprx%
if "%SPRX%"=="%PRX%" set SPRX=%PRX:.PRX=.sprx%

if not exist "%SCETOOL_EXE%" (
  echo error: scetool.exe not found at %SCETOOL_EXE%
  exit /b 1
)
if not exist "%SCETOOL_WORK_DIR%\data\keys" (
  echo error: scetool data keys not found at %SCETOOL_WORK_DIR%\data\keys
  exit /b 1
)

pushd "%SCETOOL_WORK_DIR%"
"%SCETOOL_EXE%" -0 SELF -1 TRUE -s FALSE -2 0A -3 1070000052000001 -4 01000002 -5 APP -6 0003004000000000 -A 0001000000000000 --self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002 -e "%PRX%" "%SPRX%"
set ERR=%ERRORLEVEL%
popd
if not "%ERR%"=="0" exit /b %ERR%

echo Built: %PRX%
echo Signed: %SPRX%
exit /b 0