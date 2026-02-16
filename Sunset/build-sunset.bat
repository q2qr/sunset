@echo off
setlocal

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Debug

set PLATFORM=PS3
set ROOT=C:\Users\liams\OneDrive\Documentos\Visual Studio 2013\Projects\PS3_PPU_Project1\PS3_PPU_Project1
set PROJ=%ROOT%\ps3-mc-modloader.vcxproj

if "%SCE_PS3_ROOT%"=="" set SCE_PS3_ROOT=C:\usr\local\cell
if "%SN_PS3_PATH%"=="" set SN_PS3_PATH=C:\usr\local\cell\host-win32\sn

"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "%PROJ%" /t:Build /p:Configuration=%CONFIG% /p:Platform=%PLATFORM%
if errorlevel 1 exit /b 1

echo Built: %ROOT%\PS3_Debug\sunset.prx
exit /b 0
