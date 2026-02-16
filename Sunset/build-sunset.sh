#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CONFIG="${1:-Debug}"
PLATFORM="PS3"
PROJ="$SCRIPT_DIR/ps3-mc-modloader.vcxproj"

to_win_path() {
  if command -v cygpath >/dev/null 2>&1; then
    cygpath -w "$1"
  else
    printf '%s' "$1"
  fi
}

SCRIPT_DIR_WIN="$(to_win_path "$SCRIPT_DIR")"
PROJ_WIN="$(to_win_path "$PROJ")"

export SCE_PS3_ROOT="${SCE_PS3_ROOT:-C:/usr/local/cell}"
export SN_PS3_PATH="${SN_PS3_PATH:-C:/usr/local/cell/host-win32/sn}"

MSBUILD_EXE="C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe"
SCETOOL_EXE="${SCETOOL_EXE:-C:/Users/liams/Downloads/scetool/scetool.exe}"
SCETOOL_WORK_DIR="${SCETOOL_WORK_DIR:-$SCRIPT_DIR/../dependencies/scetool/bin}"
SCETOOL_WORK_DIR_WIN="$(to_win_path "$SCETOOL_WORK_DIR")"
SCETOOL_EXE_WIN="$(to_win_path "$SCETOOL_EXE")"

powershell.exe -NoProfile -Command "& '$MSBUILD_EXE' '$PROJ_WIN' /t:Build /p:Configuration=$CONFIG /p:Platform=$PLATFORM"

PRX_PATH=""
for candidate in "$SCRIPT_DIR/PS3_Debug/sunset.prx" "$SCRIPT_DIR/PS3_Debug/Sunset.prx"; do
  if [ -f "$candidate" ]; then
    PRX_PATH="$candidate"
    break
  fi
done

if [ -z "$PRX_PATH" ]; then
  echo "error: built PRX not found in $SCRIPT_DIR/PS3_Debug" >&2
  exit 1
fi

SPRX_PATH="${PRX_PATH%.*}.sprx"
PRX_PATH_WIN="$(to_win_path "$PRX_PATH")"
SPRX_PATH_WIN="$(to_win_path "$SPRX_PATH")"

if [ ! -f "$SCETOOL_EXE" ] && [ ! -f "$SCETOOL_EXE_WIN" ]; then
  echo "error: scetool.exe not found at $SCETOOL_EXE" >&2
  exit 1
fi
if [ ! -f "$SCETOOL_WORK_DIR/data/keys" ] && [ ! -f "$SCETOOL_WORK_DIR_WIN/data/keys" ]; then
  echo "error: scetool data keys not found at $SCETOOL_WORK_DIR/data/keys" >&2
  exit 1
fi

powershell.exe -NoProfile -Command "`$tool='$SCETOOL_EXE_WIN'; `$work='$SCETOOL_WORK_DIR_WIN'; `$in='$PRX_PATH_WIN'; `$out='$SPRX_PATH_WIN'; Push-Location `$work; & `$tool -0 SELF -1 TRUE -s FALSE -2 0A -3 1070000052000001 -4 01000002 -5 APP -6 0003004000000000 -A 0001000000000000 --self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002 -e `$in `$out; `$code=`$LASTEXITCODE; Pop-Location; exit `$code"

echo "Built: $PRX_PATH"
echo "Signed: $SPRX_PATH"