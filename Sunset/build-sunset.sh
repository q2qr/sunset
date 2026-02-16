#!/usr/bin/env bash
set -euo pipefail

CONFIG="${1:-Debug}"
PLATFORM="PS3"
ROOT="C:/Users/liams/OneDrive/Documentos/Visual Studio 2013/Projects/PS3_PPU_Project1/PS3_PPU_Project1"
PROJ="$ROOT/ps3-mc-modloader.vcxproj"

export SCE_PS3_ROOT="${SCE_PS3_ROOT:-C:/usr/local/cell}"
export SN_PS3_PATH="${SN_PS3_PATH:-C:/usr/local/cell/host-win32/sn}"

powershell.exe -NoProfile -Command "& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' '$PROJ' /t:Build /p:Configuration=$CONFIG /p:Platform=$PLATFORM"

echo "Built: $ROOT/PS3_Debug/sunset.prx"
